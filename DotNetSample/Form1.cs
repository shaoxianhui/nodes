using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DotNetSample
{
    public partial class Form1 : Form
    {
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct C_CNodeInfo
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
            public char[] UID;          //设备唯一ID
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 11)]
            public char[] phoneNum;     //手机号
            public char allStatus;        //bit0:节点在线状态标识
                                          //     1 = 在线，0 = 离线
                                          //bit1:最近一次发送数据成功/失败标识
                                          //     0 = 失败，1 = 成功
                                          //bit2~bit7保留，值为0
            public int SN;                //该节点在快递查询列表的位序值（0~0xFFFFFFFF）
        }
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct C_CNodeInfoList
        {
	        public int nodeNum;
            public IntPtr nodeInfoList;
         }
        [DllImport("NodeManagerDll.dll")]
        static extern void NodeNumRequest(ref int num);
        [DllImport("NodeManagerDll.dll")]
        static extern void InitGPRS(int GPRSPort, int cmdPort, int maxNode, char[] sec);
        [DllImport("NodeManagerDll.dll")]
        static extern void NodeCmdSend(ref C_CNodeInfo c_nodeInfo, char type, short dataLen, char[] ptrData);
        [DllImport("NodeManagerDll.dll")]
        static extern void NodeInfoRequest(ref C_CNodeInfoList c_ptrNodeInfoList);
        public Form1()
        {
            InitializeComponent();
        }

        private void call_Click(object sender, EventArgs e)
        {
            int n = 100;
            NodeNumRequest(ref n);
            MessageBox.Show(n.ToString());
        }

        private void initdll_Click(object sender, EventArgs e)
        {
            char[] sec = new char[128];
            InitGPRS(9123, 9124, 100, sec);
        }

        private void nodeinfo_Click(object sender, EventArgs e)
        {
            C_CNodeInfoList list = new C_CNodeInfoList();
            list.nodeNum = 2;
            list.nodeInfoList = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(C_CNodeInfo)) * 2);
            NodeInfoRequest(ref list);
            for(int i =0; i < list.nodeNum; i++)
            {
                C_CNodeInfo m = (C_CNodeInfo)Marshal.PtrToStructure(list.nodeInfoList + i * Marshal.SizeOf(typeof(C_CNodeInfo)), typeof(C_CNodeInfo));
                MessageBox.Show(m.SN.ToString());
            }
        }

        private void sendcmd_Click(object sender, EventArgs e)
        {
            char[] data = new char[1];
            data[0] = (char)0;
            C_CNodeInfo c = new C_CNodeInfo();
            c.SN = 100;
            NodeCmdSend(ref c, (char)1, 1, data);
            //MessageBox.Show(((int)(c.phoneNum[10])).ToString());
        }
    }
}
