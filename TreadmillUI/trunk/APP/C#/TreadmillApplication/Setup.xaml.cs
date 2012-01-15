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
using System.Diagnostics;

namespace TreadmillApplication
{
	public partial class Setup
	{
		public Setup()
		{
			this.InitializeComponent();

			// Insert code required on object creation below this point.
		}
		
		private void Page_Loaded(object sender, RoutedEventArgs e)
		{
			Trace.WriteLine("Setup page loaded.");
		}
		
		private void Page_Unloaded(object sender, RoutedEventArgs e)
		{
			Trace.WriteLine("Setup page unloaded.");
		}
		
		~Setup()
		{
			Trace.WriteLine("Setup page destroyed.");
		}

		private void Button_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			// TODO: Add event handler implementation here.
			
		}
	}
}