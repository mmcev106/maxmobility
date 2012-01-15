#include "webwidget2.h"

#include <QInputMethodEvent>
#include <QDebug>
#include <QWebFrame>
#include <QWebElement>
#include <QMessageBox>

WebWidget::WebWidget(QWidget* parent) :
        QWebView(parent)
{
    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(onJavaScriptWindowObjectCleared()));
}


QVariant WebWidget::onTextFieldFocused(){
    QMessageBox::information(this, "Input Box Focused", "An HTML input box received focus!");
    return true;
}

void WebWidget::onJavaScriptWindowObjectCleared(){

    /**
      * Map the receive focus event for input boxes in webpages to this.onTextFieldFocused();
      */
    QWebFrame* mainFrame = page()->mainFrame();
    mainFrame->addToJavaScriptWindowObject("webWidget", this);
    mainFrame->documentElement().evaluateJavaScript(
        "function isTextElement(el) { "
            "return el.tagName == \"INPUT\" && el.type == \"text\"; "
        "} "
        "this.addEventListener(\"DOMFocusIn\", function(e) { "
            "if (isTextElement(e.target)) { "
                "webWidget.onTextFieldFocused(); "
            "} "
        "}, false); ");
}
