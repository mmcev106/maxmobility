#include "webview.h"

#include <QDebug>
#include <QMouseEvent>
#include <QWebFrame>
#include <QDateTime>
#include <QCoreApplication>
#include <QMessageBox>
#include <QWebElement>
#include "screens.h"
#include "keyboardscreen.h"

static int CLICK_MOVE_THRESHOLD = 10; //in pixels
static int SCROLL_THRESHOLD = 50; //in milliseconds

WebView::WebView(QWidget *parent) :
    QWebView(parent)
  ,unusedDx(0)
  ,unusedDy(0)
  ,lastScrollTime(0)
  ,clickEventListenerAdded(false)
{
    connect(this, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
    connect(this, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress(int)));
}

void WebView::mouseMoveEvent(QMouseEvent *event){

    if(event->buttons() == Qt::LeftButton){

        QPoint currentTouchPoint = event->pos();

        unusedDx += lastTouchPoint.x() - currentTouchPoint.x();
        unusedDy += lastTouchPoint.y() - currentTouchPoint.y();

        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        qint64 timeSinceLastScroll = currentTime - lastScrollTime;

        /**
         * We need to ensure that scroll calls aren't made too often
         * or the QWebView will not have enough time to repaint while
         * the user is scrolling on complex sites.
         */
        if(timeSinceLastScroll > SCROLL_THRESHOLD){

            page()->mainFrame()->scroll(unusedDx, unusedDy);
            unusedDx = 0;
            unusedDy = 0;
            lastScrollTime = currentTime;
        }

        lastTouchPoint =  event->pos();
    }
    else{
        QWebView::mouseMoveEvent(event);
    }
}

void WebView::mousePressEvent(QMouseEvent *event){

    lastPressPoint = event->pos();
    lastTouchPoint =  event->pos();

    QWebView::mousePressEvent(event);
}

void WebView::mouseReleaseEvent( QMouseEvent * event){

    QPoint currentPoint = event->pos();

    int totalDx = qAbs(currentPoint.x() - lastPressPoint.x());
    int totalDy = qAbs(currentPoint.y() - lastPressPoint.y());

    /**
      * Don't send the release event to the QWebView if the user has been scrolling.
      */
    if(totalDx < CLICK_MOVE_THRESHOLD && totalDy < CLICK_MOVE_THRESHOLD){
        QWebView::mouseReleaseEvent(event);
    }
}


void WebView::onTextFieldClicked(QString text){

    Screens::show(new KeyboardScreen(text, this));
}

void WebView::onLoadStarted(){
    clickEventListenerAdded = false;
}

void WebView::onLoadProgress(int progress){

    /**
     *  Adding the click event listener on loadStarted() doesn't work,
     *  so wait until the page has loaded at least 25%
     */
    if(!clickEventListenerAdded && progress > 25){

        /**
          * Map the receive focus event for input boxes in webpages to this.onTextFieldFocused();
          */
        QWebFrame* mainFrame = page()->mainFrame();
        mainFrame->addToJavaScriptWindowObject("webWidget", this);
        mainFrame->documentElement().evaluateJavaScript(
            "function isTextElement(el) { "
                    "return el.tagName == 'INPUT' && (el.type == 'text' || el.type == 'password'); "
            "} "
            "this.addEventListener(\"click\", function(e) { "
                "if (isTextElement(e.target)) { "
                    "webWidget.onTextFieldClicked(e.target.value); "
                "} "
            "}, false); ");

        clickEventListenerAdded = true;
    }
}
