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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TreadmillApplication
{
	/// <summary>
	/// Interaction logic for SliderWidget.xaml
	/// </summary>
	/// 
	
	public partial class SliderWidget : UserControl
	{
					
			public int Min
			{
				get { return Min; }
				set { SetValue(MinProperty, value); }
			}
			
			public static readonly DependencyProperty MinProperty =
				DependencyProperty.Register("Min", typeof(int), typeof(SliderWidget), new UIPropertyMetadata());
			
			public int currentValue
			{
				get { return currentValue; }
				set { SetValue(currentValueProperty, value); }
			}
			
			public static readonly DependencyProperty currentValueProperty =
				DependencyProperty.Register("currentValue", typeof(double), typeof(SliderWidget), new UIPropertyMetadata());
			
			
			public int Max
			{
				get { return Max; }
				set { SetValue(MaxProperty, value); }
			}
			
			public static readonly DependencyProperty MaxProperty =
				DependencyProperty.Register("Max", typeof(int), typeof(SliderWidget), new UIPropertyMetadata());
				
				
				
				
				
				
				
				
				//-----------------------------
			public SliderWidget()
			{
				InitializeComponent();
				//this.Loaded += SliderWidget_Loaded;
			}
			
//			void SliderWidget_Loaded(object sender, RoutedEventArgs e)
//			{
//				SliderWidget.ValueChanged += aSlider_ValueChanged;
//			}
//			
//			private void SliderWidget_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
//			{
//				UpperSlider.Value = aSlider.Value;
//			}
	}
}