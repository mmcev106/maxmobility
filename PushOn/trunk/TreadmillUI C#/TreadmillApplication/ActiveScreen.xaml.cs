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
	/// Interaction logic for ActiveScreen.xaml
	/// </summary>
	public partial class ActiveScreen : TabItem
	{		
		public ActiveScreen()
		{
			this.InitializeComponent();
		}
		
		public void PlayVideo(object sender, RoutedEventArgs e)
        {
            Video.Visibility = Visibility.Visible;
            Video.Play();
        }

        public void PauseVideo(object sender, RoutedEventArgs e)
        {
            Video.Visibility = Visibility.Visible;
            Video.Pause();
        }

        public void StopVideo(object sender, RoutedEventArgs e)
        {
            Video.Visibility = Visibility.Hidden;
            Video.Stop();
        }

        private void bTV_Click(object sender, System.Windows.RoutedEventArgs e)
        {
        	// TODO: Add event handler implementation here.
			PlayVideo(sender,e);
        }

        private void bTrails_Click(object sender, System.Windows.RoutedEventArgs e)
        {
        	// TODO: Add event handler implementation here.
			StopVideo(sender,e);
        }
	}
}