using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using InTheHand;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Ports;
using InTheHand.Net.Sockets;
using InTheHand.Net;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace Eyetraction
{
    public partial class Interface : Form
    {
        private GazePoint m_EyeTracker;
        private const int m_Row = 15;
        private const int m_Column = 18;
        DataGridViewCell m_cell_new;
        public Interface()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            FormBorderStyle = FormBorderStyle.None;
            WindowState = FormWindowState.Maximized;
            TopMost = true;


            for (int i = 0; i < m_Row; i++)
            {
                this.dataGridView1.Rows.Add();
                dataGridView1.Rows[i].Height = (this.Height / m_Row);
            }

            DataGridViewCellStyle style = new DataGridViewCellStyle();
            style.ForeColor = Color.Purple;


            for (int i = 0; i < m_Row; i++)
            {
                for (int j = 0; j < m_Column; j++)
                {
                   DataGridViewCell cell = dataGridView1.Rows[i].Cells[j];
                   // cell.Style = style;
                   // cell.Style.BackColor = Color.Purple;
                   // cell.ToolTipText = dataGridView1.GetCellDisplayRectangle(j, i, true).ToString();

                }
            }

            //Initialize bluetooth connection
            StartListening();

        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                this.Close();
            }
        }

        private void dataGridView1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                this.Close();
            if (e.KeyCode == Keys.T)
            {
                m_EyeTracker = new GazePoint(this);
            }
        }

        private void dataGridView1_CellMouseEnter(object sender, DataGridViewCellEventArgs e)
        {
            m_cell_new = dataGridView1.Rows[e.RowIndex].Cells[e.ColumnIndex];
            m_cell_new.Style.BackColor = Color.Green;
        }

        private void dataGridView1_CellMouseLeave(object sender, DataGridViewCellEventArgs e)
        {
            m_cell_new = dataGridView1.Rows[e.RowIndex].Cells[e.ColumnIndex];
            m_cell_new.Style.BackColor = Color.Purple;
        }

        //Bluetooth Stuff
        private static Stream blue_comm;

        private static byte[] toBytes(string str)
        {
            byte[] bytes = new byte[str.Length * sizeof(char)];
            System.Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
            return bytes;
        }

        private static byte[] toSingleBytes(byte[] bytes)
        {
            byte[] newbytes = new byte[bytes.Length / 2];
            for (int i = 0; i < bytes.Length; i += 2)
                newbytes[i / 2] = bytes[i];
            return newbytes;
        }

        private static string toString(byte[] bytes)
        {
            char[] chars = new char[bytes.Length / sizeof(char)];
            System.Buffer.BlockCopy(bytes, 0, chars, 0, bytes.Length);
            return new string(chars);
        }

        public static void StartListening()
        {
            byte[] bytes = new Byte[1024];
            string data;
            IPHostEntry ipHostInfo = Dns.Resolve(Dns.GetHostName());
            IPAddress ipAddress = ipHostInfo.AddressList[0];
            IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 11000);

            Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                listener.Bind(localEndPoint);
                listener.Listen(10);

                while (true)
                {
                    Socket handler = listener.Accept();
                    data = null;

                    while (true)
                    {
                        bytes = new byte[1024];
                        int bytesRec = handler.Receive(bytes);
                        data = Encoding.ASCII.GetString(bytes, 0, bytesRec);
                        Console.WriteLine(data);

                        if (data[0] == 'q')
                        {
                            break;
                        }
                        else if (data[0] == 'c')
                        {
                            string addr_string = data.Substring(1, 12);
                            data = "";

                            BluetoothAddress addr = BluetoothAddress.Parse(addr_string);
                            BluetoothClient client = new BluetoothClient();
                            BluetoothEndPoint other_device = new BluetoothEndPoint(addr, BluetoothService.SerialPort);

                            client.Connect(other_device);

                            blue_comm = client.GetStream();
                        }
                        else
                        {
                            handler.Send(Encoding.ASCII.GetBytes("1"));
                            Send(data);
                        }
                        data = "";

                    }
                    break;
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }

        private static void Send(String msg)
        {
            try
            {
                msg = msg.Trim();
                Console.WriteLine("Sending: " + msg);
                int length = msg.Length;
                byte[] msg_bytes = toSingleBytes(toBytes(msg));
                blue_comm.Write(msg_bytes, 0, length);
                Thread.Sleep(1000);

            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}

