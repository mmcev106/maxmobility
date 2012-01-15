using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Threading;
using System.Reflection;
using System.Windows.Interactivity;

namespace TreadmillApplication
{
	/// <summary>
	/// Interaction logic for Window1.xaml
	/// </summary>
	
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			this.InitializeComponent();
		}
	}  
 
	public class ActivateTabAction : TargetedTriggerAction<FrameworkElement>
	{
		public static readonly DependencyProperty TabNameProperty = DependencyProperty.Register("TabName", typeof(string), typeof(ActivateTabAction), new PropertyMetadata(string.Empty));
		
		public string TabName
		{
			get { return (string)GetValue(TabNameProperty); }
			set { SetValue(TabNameProperty, value); }
		}
		
		protected override void Invoke(object o)
		{
			// Find userControl or Window parent.
			var control = this.Target;
			
			while(control != null && !(control is UserControl) && !(control is Window))
			{
				control = control.Parent as FrameworkElement;
			}
			
			if(control == null || (!(control is UserControl) && !(control is Window)))
			{
				return;
			}
			
			// Find the TabItem field by its name.
			var type = control.GetType();
			var target = type.GetField(this.TabName, BindingFlags.IgnoreCase | BindingFlags.NonPublic | BindingFlags.Instance);
			
			if(target == null)
			{
				return;
			}
			
			// Get the tabitem.
			var tabItem = target.GetValue(control) as TabItem;
			if(tabItem == null)
			{
				return;
			}
			
			ActivateTab(tabItem);
			
			// Recursively search for tab controls up the visual tree to activate.
			var parent = tabItem.Parent;
			while (parent != null)
			{
				if (parent is TabItem)
				{
					ActivateTab(parent as TabItem);
				}
				if (parent is FrameworkElement)
				{
					parent = (parent as FrameworkElement).Parent;
				}
				else
				{
					parent = null;
				}
			}
		}
		
		// Find the TabItem's parent TabControl and activate the tab.
		private void ActivateTab(TabItem tabItem)
		{
			var tabControl = tabItem.Parent as TabControl;
			if (tabControl != null)
			{
				tabControl.SelectedItem = tabItem;
			}
		}
	}
}