namespace SerialPort
{
    partial class FrmSCI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmSCI));
            this.LbPortName = new System.Windows.Forms.Label();
            this.CbSCIComNum = new System.Windows.Forms.ComboBox();
            this.SetSerialPort = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.BtnSCISwitch = new System.Windows.Forms.Button();
            this.LblSCI = new System.Windows.Forms.Label();
            this.CbSCIBaud = new System.Windows.Forms.ComboBox();
            this.Baud = new System.Windows.Forms.Label();
            this.button6 = new System.Windows.Forms.Button();
            this.SerialPortSend = new System.Windows.Forms.GroupBox();
            this.LabNote = new System.Windows.Forms.Label();
            this.BtnSCISend = new System.Windows.Forms.Button();
            this.CbSCISendType = new System.Windows.Forms.ComboBox();
            this.BtnSCIClearSend = new System.Windows.Forms.Button();
            this.TbSCISend = new System.Windows.Forms.TextBox();
            this.lbType = new System.Windows.Forms.Label();
            this.SerialPortReceive = new System.Windows.Forms.GroupBox();
            this.TbShowString = new System.Windows.Forms.TextBox();
            this.BtnState = new System.Windows.Forms.Button();
            this.lbHex = new System.Windows.Forms.Label();
            this.TbShowHex = new System.Windows.Forms.TextBox();
            this.lbDec = new System.Windows.Forms.Label();
            this.TbShowDec = new System.Windows.Forms.TextBox();
            this.BtnSCIClearRec = new System.Windows.Forms.Button();
            this.lbChac = new System.Windows.Forms.Label();
            this.TSSLState = new System.Windows.Forms.ToolStripStatusLabel();
            this.sSSerialPortInfo = new System.Windows.Forms.StatusStrip();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.SetSerialPort.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SerialPortSend.SuspendLayout();
            this.SerialPortReceive.SuspendLayout();
            this.sSSerialPortInfo.SuspendLayout();
            this.SuspendLayout();
            // 
            // LbPortName
            // 
            this.LbPortName.AutoSize = true;
            this.LbPortName.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LbPortName.ForeColor = System.Drawing.Color.Black;
            this.LbPortName.Location = new System.Drawing.Point(23, 40);
            this.LbPortName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.LbPortName.Name = "LbPortName";
            this.LbPortName.Size = new System.Drawing.Size(260, 18);
            this.LbPortName.TabIndex = 0;
            this.LbPortName.Text = "串口选择(Select Serial Port)";
            // 
            // CbSCIComNum
            // 
            this.CbSCIComNum.Font = new System.Drawing.Font("黑体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CbSCIComNum.FormattingEnabled = true;
            this.CbSCIComNum.Location = new System.Drawing.Point(297, 36);
            this.CbSCIComNum.Margin = new System.Windows.Forms.Padding(4);
            this.CbSCIComNum.Name = "CbSCIComNum";
            this.CbSCIComNum.Size = new System.Drawing.Size(160, 25);
            this.CbSCIComNum.TabIndex = 1;
            this.CbSCIComNum.SelectedIndexChanged += new System.EventHandler(this.CbSCIComNum_SelectedIndexChanged);
            // 
            // SetSerialPort
            // 
            this.SetSerialPort.Controls.Add(this.pictureBox1);
            this.SetSerialPort.Controls.Add(this.BtnSCISwitch);
            this.SetSerialPort.Controls.Add(this.LblSCI);
            this.SetSerialPort.Controls.Add(this.CbSCIBaud);
            this.SetSerialPort.Controls.Add(this.Baud);
            this.SetSerialPort.Controls.Add(this.LbPortName);
            this.SetSerialPort.Controls.Add(this.CbSCIComNum);
            this.SetSerialPort.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SetSerialPort.ForeColor = System.Drawing.Color.Red;
            this.SetSerialPort.Location = new System.Drawing.Point(16, 15);
            this.SetSerialPort.Margin = new System.Windows.Forms.Padding(4);
            this.SetSerialPort.Name = "SetSerialPort";
            this.SetSerialPort.Padding = new System.Windows.Forms.Padding(4);
            this.SetSerialPort.Size = new System.Drawing.Size(1087, 151);
            this.SetSerialPort.TabIndex = 2;
            this.SetSerialPort.TabStop = false;
            this.SetSerialPort.Text = "串口设置(Setting Serial Port)";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Transparent;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.InitialImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.InitialImage")));
            this.pictureBox1.Location = new System.Drawing.Point(909, 85);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(169, 50);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 5;
            this.pictureBox1.TabStop = false;
            // 
            // BtnSCISwitch
            // 
            this.BtnSCISwitch.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BtnSCISwitch.ForeColor = System.Drawing.Color.Black;
            this.BtnSCISwitch.Location = new System.Drawing.Point(672, 85);
            this.BtnSCISwitch.Margin = new System.Windows.Forms.Padding(4);
            this.BtnSCISwitch.Name = "BtnSCISwitch";
            this.BtnSCISwitch.Size = new System.Drawing.Size(211, 40);
            this.BtnSCISwitch.TabIndex = 4;
            this.BtnSCISwitch.Text = "打开串口(Open SCI)";
            this.BtnSCISwitch.UseVisualStyleBackColor = true;
            this.BtnSCISwitch.Click += new System.EventHandler(this.BtnSCISwitch_Click);
            // 
            // LblSCI
            // 
            this.LblSCI.AutoSize = true;
            this.LblSCI.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LblSCI.ForeColor = System.Drawing.Color.Black;
            this.LblSCI.Location = new System.Drawing.Point(24, 94);
            this.LblSCI.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.LblSCI.Name = "LblSCI";
            this.LblSCI.Size = new System.Drawing.Size(0, 18);
            this.LblSCI.TabIndex = 3;
            // 
            // CbSCIBaud
            // 
            this.CbSCIBaud.Font = new System.Drawing.Font("黑体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CbSCIBaud.FormattingEnabled = true;
            this.CbSCIBaud.Items.AddRange(new object[] {
            "9600",
            "19200",
            "38400",
            "115200"});
            this.CbSCIBaud.Location = new System.Drawing.Point(865, 36);
            this.CbSCIBaud.Margin = new System.Windows.Forms.Padding(4);
            this.CbSCIBaud.Name = "CbSCIBaud";
            this.CbSCIBaud.Size = new System.Drawing.Size(160, 25);
            this.CbSCIBaud.TabIndex = 3;
            this.CbSCIBaud.SelectedIndexChanged += new System.EventHandler(this.CbSCIBaud_SelectedIndexChanged);
            // 
            // Baud
            // 
            this.Baud.AutoSize = true;
            this.Baud.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Baud.ForeColor = System.Drawing.Color.Black;
            this.Baud.Location = new System.Drawing.Point(585, 44);
            this.Baud.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Baud.Name = "Baud";
            this.Baud.Size = new System.Drawing.Size(260, 18);
            this.Baud.TabIndex = 2;
            this.Baud.Text = "波特率选择(Select Baud Rate)";
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(552, 855);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(178, 40);
            this.button6.TabIndex = 6;
            this.button6.Text = "发送时间";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // SerialPortSend
            // 
            this.SerialPortSend.Controls.Add(this.LabNote);
            this.SerialPortSend.Controls.Add(this.BtnSCISend);
            this.SerialPortSend.Controls.Add(this.CbSCISendType);
            this.SerialPortSend.Controls.Add(this.BtnSCIClearSend);
            this.SerialPortSend.Controls.Add(this.TbSCISend);
            this.SerialPortSend.Controls.Add(this.lbType);
            this.SerialPortSend.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SerialPortSend.ForeColor = System.Drawing.Color.Red;
            this.SerialPortSend.Location = new System.Drawing.Point(16, 171);
            this.SerialPortSend.Margin = new System.Windows.Forms.Padding(4);
            this.SerialPortSend.Name = "SerialPortSend";
            this.SerialPortSend.Padding = new System.Windows.Forms.Padding(4);
            this.SerialPortSend.Size = new System.Drawing.Size(1087, 158);
            this.SerialPortSend.TabIndex = 3;
            this.SerialPortSend.TabStop = false;
            this.SerialPortSend.Text = "发送数据设置(Setting Send Data)";
            // 
            // LabNote
            // 
            this.LabNote.AutoSize = true;
            this.LabNote.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabNote.ForeColor = System.Drawing.Color.Black;
            this.LabNote.Location = new System.Drawing.Point(496, 28);
            this.LabNote.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.LabNote.Name = "LabNote";
            this.LabNote.Size = new System.Drawing.Size(0, 15);
            this.LabNote.TabIndex = 7;
            // 
            // BtnSCISend
            // 
            this.BtnSCISend.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BtnSCISend.ForeColor = System.Drawing.Color.Black;
            this.BtnSCISend.Location = new System.Drawing.Point(16, 98);
            this.BtnSCISend.Margin = new System.Windows.Forms.Padding(4);
            this.BtnSCISend.Name = "BtnSCISend";
            this.BtnSCISend.Size = new System.Drawing.Size(199, 29);
            this.BtnSCISend.TabIndex = 5;
            this.BtnSCISend.Text = "发送数据(Send Data)";
            this.BtnSCISend.UseVisualStyleBackColor = true;
            this.BtnSCISend.Click += new System.EventHandler(this.BtnSCISend_Click);
            // 
            // CbSCISendType
            // 
            this.CbSCISendType.Font = new System.Drawing.Font("黑体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CbSCISendType.FormattingEnabled = true;
            this.CbSCISendType.Items.AddRange(new object[] {
            "字符串方式(String)",
            "十进制方式(Decimal)",
            "十六进制方式(Hexadecimal)"});
            this.CbSCISendType.Location = new System.Drawing.Point(185, 44);
            this.CbSCISendType.Margin = new System.Windows.Forms.Padding(4);
            this.CbSCISendType.Name = "CbSCISendType";
            this.CbSCISendType.Size = new System.Drawing.Size(212, 25);
            this.CbSCISendType.TabIndex = 1;
            this.CbSCISendType.SelectedIndexChanged += new System.EventHandler(this.CbSCISendType_SelectedIndexChanged);
            // 
            // BtnSCIClearSend
            // 
            this.BtnSCIClearSend.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BtnSCIClearSend.ForeColor = System.Drawing.Color.Black;
            this.BtnSCIClearSend.Location = new System.Drawing.Point(239, 96);
            this.BtnSCIClearSend.Margin = new System.Windows.Forms.Padding(4);
            this.BtnSCIClearSend.Name = "BtnSCIClearSend";
            this.BtnSCIClearSend.Size = new System.Drawing.Size(193, 29);
            this.BtnSCIClearSend.TabIndex = 4;
            this.BtnSCIClearSend.Text = "清空发送框(Clear)";
            this.BtnSCIClearSend.UseVisualStyleBackColor = true;
            this.BtnSCIClearSend.Click += new System.EventHandler(this.BtnSCIClearSend_Click);
            // 
            // TbSCISend
            // 
            this.TbSCISend.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TbSCISend.Location = new System.Drawing.Point(452, 54);
            this.TbSCISend.Margin = new System.Windows.Forms.Padding(4);
            this.TbSCISend.Multiline = true;
            this.TbSCISend.Name = "TbSCISend";
            this.TbSCISend.Size = new System.Drawing.Size(604, 89);
            this.TbSCISend.TabIndex = 6;
            this.TbSCISend.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TbSCISend_KeyPress);
            // 
            // lbType
            // 
            this.lbType.AutoSize = true;
            this.lbType.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbType.ForeColor = System.Drawing.Color.Black;
            this.lbType.Location = new System.Drawing.Point(37, 49);
            this.lbType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbType.Name = "lbType";
            this.lbType.Size = new System.Drawing.Size(116, 18);
            this.lbType.TabIndex = 0;
            this.lbType.Text = "选择发送方式";
            // 
            // SerialPortReceive
            // 
            this.SerialPortReceive.Controls.Add(this.TbShowString);
            this.SerialPortReceive.Controls.Add(this.BtnState);
            this.SerialPortReceive.Controls.Add(this.lbHex);
            this.SerialPortReceive.Controls.Add(this.TbShowHex);
            this.SerialPortReceive.Controls.Add(this.lbDec);
            this.SerialPortReceive.Controls.Add(this.TbShowDec);
            this.SerialPortReceive.Controls.Add(this.BtnSCIClearRec);
            this.SerialPortReceive.Controls.Add(this.lbChac);
            this.SerialPortReceive.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SerialPortReceive.ForeColor = System.Drawing.Color.Red;
            this.SerialPortReceive.Location = new System.Drawing.Point(16, 336);
            this.SerialPortReceive.Margin = new System.Windows.Forms.Padding(4);
            this.SerialPortReceive.Name = "SerialPortReceive";
            this.SerialPortReceive.Padding = new System.Windows.Forms.Padding(4);
            this.SerialPortReceive.Size = new System.Drawing.Size(1087, 486);
            this.SerialPortReceive.TabIndex = 7;
            this.SerialPortReceive.TabStop = false;
            this.SerialPortReceive.Text = "接收数据设置(Setting Receiving Data)";
            // 
            // TbShowString
            // 
            this.TbShowString.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TbShowString.Location = new System.Drawing.Point(203, 36);
            this.TbShowString.Margin = new System.Windows.Forms.Padding(4);
            this.TbShowString.Multiline = true;
            this.TbShowString.Name = "TbShowString";
            this.TbShowString.ReadOnly = true;
            this.TbShowString.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.TbShowString.Size = new System.Drawing.Size(852, 114);
            this.TbShowString.TabIndex = 16;
            // 
            // BtnState
            // 
            this.BtnState.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BtnState.ForeColor = System.Drawing.Color.Black;
            this.BtnState.Location = new System.Drawing.Point(703, 444);
            this.BtnState.Margin = new System.Windows.Forms.Padding(4);
            this.BtnState.Name = "BtnState";
            this.BtnState.Size = new System.Drawing.Size(180, 29);
            this.BtnState.TabIndex = 15;
            this.BtnState.Text = "隐藏状态条(Hide)";
            this.BtnState.UseVisualStyleBackColor = true;
            this.BtnState.Click += new System.EventHandler(this.BtnState_Click);
            // 
            // lbHex
            // 
            this.lbHex.AutoSize = true;
            this.lbHex.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbHex.ForeColor = System.Drawing.Color.Black;
            this.lbHex.Location = new System.Drawing.Point(15, 365);
            this.lbHex.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbHex.Name = "lbHex";
            this.lbHex.Size = new System.Drawing.Size(161, 18);
            this.lbHex.TabIndex = 14;
            this.lbHex.Text = "十六进制显示(Hex)";
            // 
            // TbShowHex
            // 
            this.TbShowHex.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TbShowHex.Location = new System.Drawing.Point(203, 308);
            this.TbShowHex.Margin = new System.Windows.Forms.Padding(4);
            this.TbShowHex.Multiline = true;
            this.TbShowHex.Name = "TbShowHex";
            this.TbShowHex.ReadOnly = true;
            this.TbShowHex.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.TbShowHex.Size = new System.Drawing.Size(852, 114);
            this.TbShowHex.TabIndex = 13;
            // 
            // lbDec
            // 
            this.lbDec.AutoSize = true;
            this.lbDec.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbDec.ForeColor = System.Drawing.Color.Black;
            this.lbDec.Location = new System.Drawing.Point(24, 222);
            this.lbDec.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbDec.Name = "lbDec";
            this.lbDec.Size = new System.Drawing.Size(143, 18);
            this.lbDec.TabIndex = 10;
            this.lbDec.Text = "十进制显示(Dec)";
            // 
            // TbShowDec
            // 
            this.TbShowDec.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TbShowDec.Location = new System.Drawing.Point(203, 169);
            this.TbShowDec.Margin = new System.Windows.Forms.Padding(4);
            this.TbShowDec.Multiline = true;
            this.TbShowDec.Name = "TbShowDec";
            this.TbShowDec.ReadOnly = true;
            this.TbShowDec.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.TbShowDec.Size = new System.Drawing.Size(852, 118);
            this.TbShowDec.TabIndex = 9;
            // 
            // BtnSCIClearRec
            // 
            this.BtnSCIClearRec.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BtnSCIClearRec.ForeColor = System.Drawing.Color.Black;
            this.BtnSCIClearRec.Location = new System.Drawing.Point(452, 444);
            this.BtnSCIClearRec.Margin = new System.Windows.Forms.Padding(4);
            this.BtnSCIClearRec.Name = "BtnSCIClearRec";
            this.BtnSCIClearRec.Size = new System.Drawing.Size(165, 29);
            this.BtnSCIClearRec.TabIndex = 8;
            this.BtnSCIClearRec.Text = "清空接收框(Clear)";
            this.BtnSCIClearRec.UseVisualStyleBackColor = true;
            this.BtnSCIClearRec.Click += new System.EventHandler(this.btnClearRec_Click);
            // 
            // lbChac
            // 
            this.lbChac.AutoSize = true;
            this.lbChac.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbChac.ForeColor = System.Drawing.Color.Black;
            this.lbChac.Location = new System.Drawing.Point(23, 84);
            this.lbChac.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbChac.Name = "lbChac";
            this.lbChac.Size = new System.Drawing.Size(170, 18);
            this.lbChac.TabIndex = 7;
            this.lbChac.Text = "字符串显示(String)";
            // 
            // TSSLState
            // 
            this.TSSLState.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TSSLState.Name = "TSSLState";
            this.TSSLState.Size = new System.Drawing.Size(89, 18);
            this.TSSLState.Text = "没有操作!";
            // 
            // sSSerialPortInfo
            // 
            this.sSSerialPortInfo.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.sSSerialPortInfo.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.TSSLState});
            this.sSSerialPortInfo.Location = new System.Drawing.Point(0, 947);
            this.sSSerialPortInfo.Name = "sSSerialPortInfo";
            this.sSSerialPortInfo.Padding = new System.Windows.Forms.Padding(1, 0, 19, 0);
            this.sSSerialPortInfo.Size = new System.Drawing.Size(1124, 24);
            this.sSSerialPortInfo.TabIndex = 8;
            this.sSSerialPortInfo.Text = "statusStrip1";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(77, 839);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(115, 72);
            this.button1.TabIndex = 17;
            this.button1.Text = "开";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(236, 839);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(111, 72);
            this.button2.TabIndex = 17;
            this.button2.Text = "关";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.SystemColors.Highlight;
            this.button3.Location = new System.Drawing.Point(413, 839);
            this.button3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 22);
            this.button3.TabIndex = 17;
            this.button3.Text = "蓝";
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.Color.Lime;
            this.button4.Location = new System.Drawing.Point(413, 868);
            this.button4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 22);
            this.button4.TabIndex = 17;
            this.button4.Text = "绿";
            this.button4.UseVisualStyleBackColor = false;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.BackColor = System.Drawing.Color.Red;
            this.button5.Location = new System.Drawing.Point(413, 898);
            this.button5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 22);
            this.button5.TabIndex = 17;
            this.button5.Text = "红";
            this.button5.UseVisualStyleBackColor = false;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(779, 847);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(153, 56);
            this.button7.TabIndex = 18;
            this.button7.Text = "txt";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // FrmSCI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1124, 971);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.sSSerialPortInfo);
            this.Controls.Add(this.SerialPortReceive);
            this.Controls.Add(this.SerialPortSend);
            this.Controls.Add(this.SetSerialPort);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "FrmSCI";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "串口测试工程(苏州大学飞思卡尔嵌入式系统研究中心)";
            this.Load += new System.EventHandler(this.FrmSCI_Load);
            this.SetSerialPort.ResumeLayout(false);
            this.SetSerialPort.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.SerialPortSend.ResumeLayout(false);
            this.SerialPortSend.PerformLayout();
            this.SerialPortReceive.ResumeLayout(false);
            this.SerialPortReceive.PerformLayout();
            this.sSSerialPortInfo.ResumeLayout(false);
            this.sSSerialPortInfo.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label LbPortName;
        private System.Windows.Forms.ComboBox CbSCIComNum;
        private System.Windows.Forms.GroupBox SetSerialPort;
        private System.Windows.Forms.Label Baud;
        private System.Windows.Forms.ComboBox CbSCIBaud;
        private System.Windows.Forms.Label LblSCI;
        private System.Windows.Forms.Button BtnSCISwitch;
        private System.Windows.Forms.GroupBox SerialPortSend;
        private System.Windows.Forms.TextBox TbSCISend;
        private System.Windows.Forms.GroupBox SerialPortReceive;
        private System.Windows.Forms.Button BtnSCISend;
        private System.Windows.Forms.ComboBox CbSCISendType;
        private System.Windows.Forms.Button BtnSCIClearSend;
        private System.Windows.Forms.Label lbType;
        private System.Windows.Forms.Label lbChac;
        private System.Windows.Forms.Button BtnSCIClearRec;
        private System.Windows.Forms.TextBox TbShowDec;
        private System.Windows.Forms.Label lbDec;
        private System.Windows.Forms.TextBox TbShowHex;
        private System.Windows.Forms.Label lbHex;
        private System.Windows.Forms.Label LabNote;
        private System.Windows.Forms.Button BtnState;
        private System.Windows.Forms.TextBox TbShowString;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ToolStripStatusLabel TSSLState;
        private System.Windows.Forms.StatusStrip sSSerialPortInfo;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
    }
}

