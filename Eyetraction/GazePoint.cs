using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using TETCSharpClient;
using TETCSharpClient.Data;


namespace Eyetraction
{
    public class GazePoint : IGazeListener
    {
        double last_x = 0;
        double last_y = 0;
        public GazePoint(Eyetraction.Interface UI)
        {
            // Connect client
            GazeManager.Instance.Activate(GazeManager.ApiVersion.VERSION_1_0, GazeManager.ClientMode.Push);
            // Register this class for events
            GazeManager.Instance.AddGazeListener(this);
        }

        public void OnGazeUpdate(GazeData gazeData)
        {
            double gX = gazeData.SmoothedCoordinates.X;
            double gY = gazeData.SmoothedCoordinates.Y;
            System.Console.WriteLine("X = {0} and Y = {1}", gX, gY);
            Win32.SetCursorPos((int)gX, (int)gY);
        }
        ~GazePoint()
        {
            // Disconnect client
            System.Console.WriteLine("*****************************DISCONNECTING CONNECTION************************");
            GazeManager.Instance.Deactivate();
        }
    }
}
