namespace DotNetSample
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.call = new System.Windows.Forms.Button();
            this.initdll = new System.Windows.Forms.Button();
            this.nodeinfo = new System.Windows.Forms.Button();
            this.sendcmd = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // call
            // 
            this.call.Location = new System.Drawing.Point(45, 77);
            this.call.Name = "call";
            this.call.Size = new System.Drawing.Size(75, 23);
            this.call.TabIndex = 0;
            this.call.Text = "节点个数";
            this.call.UseVisualStyleBackColor = true;
            this.call.Click += new System.EventHandler(this.call_Click);
            // 
            // initdll
            // 
            this.initdll.Location = new System.Drawing.Point(45, 33);
            this.initdll.Name = "initdll";
            this.initdll.Size = new System.Drawing.Size(75, 23);
            this.initdll.TabIndex = 1;
            this.initdll.Text = "INITDLL";
            this.initdll.UseVisualStyleBackColor = true;
            this.initdll.Click += new System.EventHandler(this.initdll_Click);
            // 
            // nodeinfo
            // 
            this.nodeinfo.Location = new System.Drawing.Point(45, 127);
            this.nodeinfo.Name = "nodeinfo";
            this.nodeinfo.Size = new System.Drawing.Size(75, 23);
            this.nodeinfo.TabIndex = 2;
            this.nodeinfo.Text = "获得列表";
            this.nodeinfo.UseVisualStyleBackColor = true;
            this.nodeinfo.Click += new System.EventHandler(this.nodeinfo_Click);
            // 
            // sendcmd
            // 
            this.sendcmd.Location = new System.Drawing.Point(45, 173);
            this.sendcmd.Name = "sendcmd";
            this.sendcmd.Size = new System.Drawing.Size(75, 23);
            this.sendcmd.TabIndex = 3;
            this.sendcmd.Text = "发送命令";
            this.sendcmd.UseVisualStyleBackColor = true;
            this.sendcmd.Click += new System.EventHandler(this.sendcmd_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.sendcmd);
            this.Controls.Add(this.nodeinfo);
            this.Controls.Add(this.initdll);
            this.Controls.Add(this.call);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button call;
        private System.Windows.Forms.Button initdll;
        private System.Windows.Forms.Button nodeinfo;
        private System.Windows.Forms.Button sendcmd;
    }
}

