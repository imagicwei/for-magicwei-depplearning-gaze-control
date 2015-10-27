#pragma once

namespace GazeControl {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

		//宣告Xtion所需要的變數
		XtionControl* myXtion;
		System::Drawing::Bitmap^ ColorImage;
		System::Drawing::Bitmap^ FinalImage;
		System::Drawing::Bitmap^ DepthImage;
		unsigned char* DepthViewBuffer;
	private: System::Windows::Forms::RadioButton^  radioButtonObject1;
	public: 
	private: System::Windows::Forms::RadioButton^  radioButtonObject2;
	private: System::Windows::Forms::RadioButton^  radioButtonObject4;
	private: System::Windows::Forms::RadioButton^  radioButtonObject3;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  buttonRunStrategy;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox_FaceRegionX;
	private: System::Windows::Forms::TextBox^  textBox_FaceRegionY;
	private: System::Windows::Forms::TextBox^  textBox_FaceRegionHeight;
	private: System::Windows::Forms::TextBox^  textBox_FaceRegionWidth;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  buttonApply;
	private: System::Windows::Forms::Button^  buttonDetectEyeRegion;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox_EyeGaryTH;
	private: System::Windows::Forms::Label^  labelVision_DAnumbers;
	private: System::Windows::Forms::Label^  labelVision_EDnumbers;
	private: System::Windows::Forms::Label^  label78;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TrackBar^  trackBarVision_DA;
	private: System::Windows::Forms::TrackBar^  trackBarVision_ED;
	private: System::Windows::Forms::GroupBox^  groupBoxRx;






	private: System::Windows::Forms::Label^  labelSensorMagAzimuth;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  labelRxBodyDoing;
	private: System::Windows::Forms::Label^  label8;


	private: System::Windows::Forms::Label^  labelRxPanPosAng;
	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::Label^  labelRxPanPos;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  labelRxTiltPosAng;
	private: System::Windows::Forms::Label^  label39;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::Label^  labelRxTiltPos;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  labelRxDipBinary3;
	private: System::Windows::Forms::Label^  labelRxDipBinary5;
	private: System::Windows::Forms::Label^  labelRxDipBinary0;
	private: System::Windows::Forms::Label^  labelRxDipBinary1;
	private: System::Windows::Forms::Label^  labelRxDipBinary2;
	private: System::Windows::Forms::Label^  labelRxDipBinary4;
	private: System::Windows::Forms::Label^  labelRxDip;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::GroupBox^  groupBoxTx;
	private: System::Windows::Forms::Label^  labelTxPanPosAng;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Label^  labelTxPanPos;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  labelTxTiltPosAng;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  labelTxTiltPos;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  labelTxHeadMotion;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  labelTxAngle;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  labelTxDis;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  labelTxBodyMotion;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::IO::Ports::SerialPort^  serialPortRS232;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  labelRobotHeadSearchState;
	private: System::Windows::Forms::Label^  labelRobotStableWait;
	private: System::Windows::Forms::Label^  labelRelativeAzimuth;
	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  labelIsBodyMotionDone;

	public: 
		System::Drawing::Bitmap^ LastDepthImage;

		void MainDisplay(void);
		System::Drawing::Bitmap^ DrawColorImage(unsigned char* iImageBuffer);
		System::Drawing::Bitmap^ DrawDepthImage(short** iImageBuffer);
		System::Drawing::Bitmap^ DrawDepthColorImageMix( float iTransparent );
		System::Drawing::Bitmap^ DrawSkeletononDepthColorImage();

		//打開 main form 時，一併打開這些form
// 		HuroCup2014Beijing::SetEventParameters^ setEventParaForm;
// 		HuroCup2014Beijing::SetEventParaAdult^ setEventParaAdult;
// 		HuroCup2014Beijing::WatchEventPara^ watchEventParaForm;

		//Color Wheel
		int startHAng, endHAng;
		int startSRadius, endSRadius;
		int vUP, vDown;

		bool dotMove;
		int dotMoveNumber;

		bool vLineMove;
		bool vUpLineMove;

		PointF H1S1, H1S2, H2S1, H2S2;

		// Frame Stopwatch
		int framePerSecond;

		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
			//載入圖片
			colorWheelBmpFileRead = gcnew Bitmap(".\\Resource\\colorWheel.bmp");
			grayLevelBmpFileRead = gcnew Bitmap(".\\Resource\\grayLevel.bmp");

			//複製一份圖片
			colorWheelBmpUsing = gcnew Bitmap( colorWheelBmpFileRead );
			pictureBoxColorWheel->Image = colorWheelBmpUsing;

			grayLevelBmpUsing = gcnew Bitmap( grayLevelBmpFileRead );
			pictureBoxGrayLevel->Image = grayLevelBmpUsing;

			//設定 Color Wheel 畫布
			colorWheelGraphics =  Graphics::FromImage(colorWheelBmpUsing);
			this->colorWheelEdge = gcnew Pen ( Color::Black,1);
			this->colorWheelDot = gcnew Pen ( Color::Red, 2 );
			this->colorWheelGraphics->DrawArc( this->colorWheelEdge, 0,0,181,181,0,360 );
			pictureBoxColorWheel->Refresh();

			//設定 Gray Level 畫布
			grayLevelGraphics =  Graphics::FromImage(grayLevelBmpUsing);
			this->grayLevelEdge = gcnew Pen ( Color::Red,2);
			pictureBoxGrayLevel->Refresh();

			//HSV initial
			startHAng, endHAng = 0;
			startSRadius, endSRadius = 0;
			vUP, vDown = 0;

			dotMove = false;
			vLineMove, vUpLineMove = false;

			H1S1 = PointF(90,90);
			H1S2 = PointF(90,90);
			H2S1 = PointF(90,90);
			H1S2 = PointF(90,90);

		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^  pictureBoxCamOneInput;
	protected: 
	private: System::Windows::Forms::PictureBox^  pictureBoxGaze;
	private: System::Windows::Forms::PictureBox^  pictureBoxCamXtionInput;

	private: System::Windows::Forms::Button^  buttonOpenCamOne;
	private: System::Windows::Forms::Button^  buttonOpenCamTwo;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorkerCam1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelMainPointX;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelMainPointY;
	private: System::Windows::Forms::Button^  buttonSetCam;
	private: System::Windows::Forms::TabControl^  tabControlColor;
	private: System::Windows::Forms::TabPage^  tabPageColorWheel;
	private: System::Windows::Forms::Button^  buttonLoadColor;
	private: System::Windows::Forms::Button^  buttonSaveColor;
	private: System::Windows::Forms::Label^  labelColorVMax;
	private: System::Windows::Forms::Label^  labelColorSMax;
	private: System::Windows::Forms::Label^  labelColorHMax;
	private: System::Windows::Forms::Label^  labelColorVi;
	private: System::Windows::Forms::Label^  labelColorSi;
	private: System::Windows::Forms::Label^  labelColorHi;
	private: System::Windows::Forms::Label^  labelColorVMin;
	private: System::Windows::Forms::Label^  labelColorVName;
	private: System::Windows::Forms::Label^  labelColorVMove;
	private: System::Windows::Forms::Label^  labelColorSMove;
	private: System::Windows::Forms::Label^  labelColorVMoveName;
	private: System::Windows::Forms::Label^  labelColorSMin;
	private: System::Windows::Forms::Label^  labelColorSMoveName;
	private: System::Windows::Forms::Label^  labelColorSName;
	private: System::Windows::Forms::Label^  labelColorHMove;
	private: System::Windows::Forms::Label^  labelColorHMoveName;
	private: System::Windows::Forms::Label^  labelColorHMin;
	private: System::Windows::Forms::Label^  labelColorHName;
	private: System::Windows::Forms::PictureBox^  pictureBoxGrayLevel;
	private: System::Windows::Forms::PictureBox^  pictureBoxColorWheel;
	private: System::Windows::Forms::TabPage^  tabPageScrollBar;
	private: System::Windows::Forms::Button^  buttonLoadColor2;
	private: System::Windows::Forms::Button^  buttonSaveColor2;
	private: System::Windows::Forms::TextBox^  textBoxColor3Max;
	private: System::Windows::Forms::TextBox^  textBoxColor3Min;
	private: System::Windows::Forms::TextBox^  textBoxColor2Max;
	private: System::Windows::Forms::TextBox^  textBoxColor2Min;
	private: System::Windows::Forms::TextBox^  textBoxColor1Max;
	private: System::Windows::Forms::TextBox^  textBoxColor1Min;
	private: System::Windows::Forms::HScrollBar^  hScrollBarColor3Max;
	private: System::Windows::Forms::HScrollBar^  hScrollBarColor3Min;
	private: System::Windows::Forms::HScrollBar^  hScrollBarColor2Max;
	private: System::Windows::Forms::HScrollBar^  hScrollBarColor2Min;
	private: System::Windows::Forms::HScrollBar^  hScrollBarColor1Max;
	private: System::Windows::Forms::HScrollBar^  hScrollBarColor1Min;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelFPS;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelMousePointH;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel5;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelMousePointS;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel6;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelMousePointV;

/*-----------------------------------------------------*/
		private: Graphics^ colorWheelGraphics;
		private: Bitmap^ colorWheelBmpFileRead;
		private: Bitmap^ colorWheelBmpUsing;
		private: Pen^ colorWheelEdge;
		private: Pen^ colorWheelDot;

		private: Graphics^ grayLevelGraphics;
		private: Bitmap^ grayLevelBmpFileRead;
		private: Bitmap^ grayLevelBmpUsing;
		private: Pen^ grayLevelEdge;

		private: array<PointF>^ pts;
private: System::ComponentModel::IContainer^  components;
		 /*-------------------------------------------------------*/
	
protected: 

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBoxCamOneInput = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxGaze = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxCamXtionInput = (gcnew System::Windows::Forms::PictureBox());
			this->buttonOpenCamOne = (gcnew System::Windows::Forms::Button());
			this->buttonOpenCamTwo = (gcnew System::Windows::Forms::Button());
			this->backgroundWorkerCam1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelMainPointX = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelMainPointY = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelFPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelMousePointH = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel5 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelMousePointS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel6 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelMousePointV = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->buttonSetCam = (gcnew System::Windows::Forms::Button());
			this->tabControlColor = (gcnew System::Windows::Forms::TabControl());
			this->tabPageColorWheel = (gcnew System::Windows::Forms::TabPage());
			this->buttonLoadColor = (gcnew System::Windows::Forms::Button());
			this->buttonSaveColor = (gcnew System::Windows::Forms::Button());
			this->labelColorVMax = (gcnew System::Windows::Forms::Label());
			this->labelColorSMax = (gcnew System::Windows::Forms::Label());
			this->labelColorHMax = (gcnew System::Windows::Forms::Label());
			this->labelColorVi = (gcnew System::Windows::Forms::Label());
			this->labelColorSi = (gcnew System::Windows::Forms::Label());
			this->labelColorHi = (gcnew System::Windows::Forms::Label());
			this->labelColorVMin = (gcnew System::Windows::Forms::Label());
			this->labelColorVName = (gcnew System::Windows::Forms::Label());
			this->labelColorVMove = (gcnew System::Windows::Forms::Label());
			this->labelColorSMove = (gcnew System::Windows::Forms::Label());
			this->labelColorVMoveName = (gcnew System::Windows::Forms::Label());
			this->labelColorSMin = (gcnew System::Windows::Forms::Label());
			this->labelColorSMoveName = (gcnew System::Windows::Forms::Label());
			this->labelColorSName = (gcnew System::Windows::Forms::Label());
			this->labelColorHMove = (gcnew System::Windows::Forms::Label());
			this->labelColorHMoveName = (gcnew System::Windows::Forms::Label());
			this->labelColorHMin = (gcnew System::Windows::Forms::Label());
			this->labelColorHName = (gcnew System::Windows::Forms::Label());
			this->pictureBoxGrayLevel = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxColorWheel = (gcnew System::Windows::Forms::PictureBox());
			this->tabPageScrollBar = (gcnew System::Windows::Forms::TabPage());
			this->buttonLoadColor2 = (gcnew System::Windows::Forms::Button());
			this->buttonSaveColor2 = (gcnew System::Windows::Forms::Button());
			this->textBoxColor3Max = (gcnew System::Windows::Forms::TextBox());
			this->textBoxColor3Min = (gcnew System::Windows::Forms::TextBox());
			this->textBoxColor2Max = (gcnew System::Windows::Forms::TextBox());
			this->textBoxColor2Min = (gcnew System::Windows::Forms::TextBox());
			this->textBoxColor1Max = (gcnew System::Windows::Forms::TextBox());
			this->textBoxColor1Min = (gcnew System::Windows::Forms::TextBox());
			this->hScrollBarColor3Max = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBarColor3Min = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBarColor2Max = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBarColor2Min = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBarColor1Max = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBarColor1Min = (gcnew System::Windows::Forms::HScrollBar());
			this->radioButtonObject1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonObject2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonObject4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonObject3 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonRunStrategy = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox_FaceRegionX = (gcnew System::Windows::Forms::TextBox());
			this->textBox_FaceRegionY = (gcnew System::Windows::Forms::TextBox());
			this->textBox_FaceRegionHeight = (gcnew System::Windows::Forms::TextBox());
			this->textBox_FaceRegionWidth = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonApply = (gcnew System::Windows::Forms::Button());
			this->buttonDetectEyeRegion = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox_EyeGaryTH = (gcnew System::Windows::Forms::TextBox());
			this->labelVision_DAnumbers = (gcnew System::Windows::Forms::Label());
			this->labelVision_EDnumbers = (gcnew System::Windows::Forms::Label());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->trackBarVision_DA = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarVision_ED = (gcnew System::Windows::Forms::TrackBar());
			this->groupBoxRx = (gcnew System::Windows::Forms::GroupBox());
			this->labelSensorMagAzimuth = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->labelRxBodyDoing = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->labelRxPanPosAng = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->labelRxPanPos = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->labelRxTiltPosAng = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->labelRxTiltPos = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->labelRxDipBinary3 = (gcnew System::Windows::Forms::Label());
			this->labelRxDipBinary5 = (gcnew System::Windows::Forms::Label());
			this->labelRxDipBinary0 = (gcnew System::Windows::Forms::Label());
			this->labelRxDipBinary1 = (gcnew System::Windows::Forms::Label());
			this->labelRxDipBinary2 = (gcnew System::Windows::Forms::Label());
			this->labelRxDipBinary4 = (gcnew System::Windows::Forms::Label());
			this->labelRxDip = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->groupBoxTx = (gcnew System::Windows::Forms::GroupBox());
			this->labelTxPanPosAng = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->labelTxPanPos = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->labelTxTiltPosAng = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->labelTxTiltPos = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->labelTxHeadMotion = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->labelTxAngle = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->labelTxDis = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->labelTxBodyMotion = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->serialPortRS232 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->labelRobotHeadSearchState = (gcnew System::Windows::Forms::Label());
			this->labelRobotStableWait = (gcnew System::Windows::Forms::Label());
			this->labelRelativeAzimuth = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->labelIsBodyMotionDone = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxCamOneInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxGaze))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxCamXtionInput))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->tabControlColor->SuspendLayout();
			this->tabPageColorWheel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxGrayLevel))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxColorWheel))->BeginInit();
			this->tabPageScrollBar->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarVision_DA))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarVision_ED))->BeginInit();
			this->groupBoxRx->SuspendLayout();
			this->groupBoxTx->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBoxCamOneInput
			// 
			this->pictureBoxCamOneInput->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pictureBoxCamOneInput->Location = System::Drawing::Point(12, 12);
			this->pictureBoxCamOneInput->Name = L"pictureBoxCamOneInput";
			this->pictureBoxCamOneInput->Size = System::Drawing::Size(320, 240);
			this->pictureBoxCamOneInput->TabIndex = 0;
			this->pictureBoxCamOneInput->TabStop = false;
			this->pictureBoxCamOneInput->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxCamOneInput_MouseClick);
			this->pictureBoxCamOneInput->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxCamOneInput_MouseMove);
			// 
			// pictureBoxGaze
			// 
			this->pictureBoxGaze->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pictureBoxGaze->Location = System::Drawing::Point(338, 12);
			this->pictureBoxGaze->Name = L"pictureBoxGaze";
			this->pictureBoxGaze->Size = System::Drawing::Size(320, 240);
			this->pictureBoxGaze->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBoxGaze->TabIndex = 1;
			this->pictureBoxGaze->TabStop = false;
			this->pictureBoxGaze->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxGaze_MouseClick);
			this->pictureBoxGaze->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxGaze_MouseMove);
			// 
			// pictureBoxCamXtionInput
			// 
			this->pictureBoxCamXtionInput->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pictureBoxCamXtionInput->Location = System::Drawing::Point(664, 12);
			this->pictureBoxCamXtionInput->Name = L"pictureBoxCamXtionInput";
			this->pictureBoxCamXtionInput->Size = System::Drawing::Size(320, 240);
			this->pictureBoxCamXtionInput->TabIndex = 2;
			this->pictureBoxCamXtionInput->TabStop = false;
			// 
			// buttonOpenCamOne
			// 
			this->buttonOpenCamOne->BackColor = System::Drawing::SystemColors::Control;
			this->buttonOpenCamOne->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->buttonOpenCamOne->Location = System::Drawing::Point(524, 276);
			this->buttonOpenCamOne->Name = L"buttonOpenCamOne";
			this->buttonOpenCamOne->Size = System::Drawing::Size(110, 50);
			this->buttonOpenCamOne->TabIndex = 3;
			this->buttonOpenCamOne->Text = L"Open Cam one";
			this->buttonOpenCamOne->UseVisualStyleBackColor = false;
			this->buttonOpenCamOne->Click += gcnew System::EventHandler(this, &Form1::buttonOpenCamOne_Click);
			// 
			// buttonOpenCamTwo
			// 
			this->buttonOpenCamTwo->BackColor = System::Drawing::SystemColors::Control;
			this->buttonOpenCamTwo->Enabled = false;
			this->buttonOpenCamTwo->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->buttonOpenCamTwo->Location = System::Drawing::Point(640, 277);
			this->buttonOpenCamTwo->Name = L"buttonOpenCamTwo";
			this->buttonOpenCamTwo->Size = System::Drawing::Size(110, 50);
			this->buttonOpenCamTwo->TabIndex = 4;
			this->buttonOpenCamTwo->Text = L"Open Cam two";
			this->buttonOpenCamTwo->UseVisualStyleBackColor = false;
			this->buttonOpenCamTwo->Click += gcnew System::EventHandler(this, &Form1::buttonOpenCamTwo_Click);
			// 
			// backgroundWorkerCam1
			// 
			this->backgroundWorkerCam1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorkerCam1_DoWork);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {this->toolStripStatusLabel1, 
				this->toolStripStatusLabelMainPointX, this->toolStripStatusLabel3, this->toolStripStatusLabelMainPointY, this->toolStripStatusLabel2, 
				this->toolStripStatusLabelFPS, this->toolStripStatusLabel4, this->toolStripStatusLabelMousePointH, this->toolStripStatusLabel5, 
				this->toolStripStatusLabelMousePointS, this->toolStripStatusLabel6, this->toolStripStatusLabelMousePointV});
			this->statusStrip1->Location = System::Drawing::Point(3, 561);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(994, 22);
			this->statusStrip1->TabIndex = 5;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(98, 17);
			this->toolStripStatusLabel1->Text = L"ObjectMain X =";
			// 
			// toolStripStatusLabelMainPointX
			// 
			this->toolStripStatusLabelMainPointX->Name = L"toolStripStatusLabelMainPointX";
			this->toolStripStatusLabelMainPointX->Size = System::Drawing::Size(29, 17);
			this->toolStripStatusLabelMainPointX->Text = L"160";
			// 
			// toolStripStatusLabel3
			// 
			this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
			this->toolStripStatusLabel3->Size = System::Drawing::Size(106, 17);
			this->toolStripStatusLabel3->Text = L"|| ObjectMainY = ";
			// 
			// toolStripStatusLabelMainPointY
			// 
			this->toolStripStatusLabelMainPointY->Name = L"toolStripStatusLabelMainPointY";
			this->toolStripStatusLabelMainPointY->Size = System::Drawing::Size(29, 17);
			this->toolStripStatusLabelMainPointY->Text = L"120";
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(46, 17);
			this->toolStripStatusLabel2->Text = L"|| FPS : ";
			// 
			// toolStripStatusLabelFPS
			// 
			this->toolStripStatusLabelFPS->Name = L"toolStripStatusLabelFPS";
			this->toolStripStatusLabelFPS->Size = System::Drawing::Size(14, 17);
			this->toolStripStatusLabelFPS->Text = L"x";
			// 
			// toolStripStatusLabel4
			// 
			this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
			this->toolStripStatusLabel4->Size = System::Drawing::Size(78, 17);
			this->toolStripStatusLabel4->Text = L"|| Color : H =";
			// 
			// toolStripStatusLabelMousePointH
			// 
			this->toolStripStatusLabelMousePointH->Name = L"toolStripStatusLabelMousePointH";
			this->toolStripStatusLabelMousePointH->Size = System::Drawing::Size(14, 17);
			this->toolStripStatusLabelMousePointH->Text = L"x";
			// 
			// toolStripStatusLabel5
			// 
			this->toolStripStatusLabel5->Name = L"toolStripStatusLabel5";
			this->toolStripStatusLabel5->Size = System::Drawing::Size(30, 17);
			this->toolStripStatusLabel5->Text = L" S =";
			// 
			// toolStripStatusLabelMousePointS
			// 
			this->toolStripStatusLabelMousePointS->Name = L"toolStripStatusLabelMousePointS";
			this->toolStripStatusLabelMousePointS->Size = System::Drawing::Size(14, 17);
			this->toolStripStatusLabelMousePointS->Text = L"x";
			// 
			// toolStripStatusLabel6
			// 
			this->toolStripStatusLabel6->Name = L"toolStripStatusLabel6";
			this->toolStripStatusLabel6->Size = System::Drawing::Size(31, 17);
			this->toolStripStatusLabel6->Text = L" V =";
			// 
			// toolStripStatusLabelMousePointV
			// 
			this->toolStripStatusLabelMousePointV->Name = L"toolStripStatusLabelMousePointV";
			this->toolStripStatusLabelMousePointV->Size = System::Drawing::Size(14, 17);
			this->toolStripStatusLabelMousePointV->Text = L"x";
			// 
			// buttonSetCam
			// 
			this->buttonSetCam->BackColor = System::Drawing::SystemColors::Control;
			this->buttonSetCam->Enabled = false;
			this->buttonSetCam->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->buttonSetCam->Location = System::Drawing::Point(639, 329);
			this->buttonSetCam->Name = L"buttonSetCam";
			this->buttonSetCam->Size = System::Drawing::Size(110, 50);
			this->buttonSetCam->TabIndex = 6;
			this->buttonSetCam->Text = L"Set Cam One";
			this->buttonSetCam->UseVisualStyleBackColor = false;
			this->buttonSetCam->Click += gcnew System::EventHandler(this, &Form1::buttonSetCam_Click);
			// 
			// tabControlColor
			// 
			this->tabControlColor->Controls->Add(this->tabPageColorWheel);
			this->tabControlColor->Controls->Add(this->tabPageScrollBar);
			this->tabControlColor->Location = System::Drawing::Point(755, 268);
			this->tabControlColor->Name = L"tabControlColor";
			this->tabControlColor->SelectedIndex = 0;
			this->tabControlColor->Size = System::Drawing::Size(229, 264);
			this->tabControlColor->TabIndex = 32;
			// 
			// tabPageColorWheel
			// 
			this->tabPageColorWheel->BackColor = System::Drawing::SystemColors::Control;
			this->tabPageColorWheel->Controls->Add(this->buttonLoadColor);
			this->tabPageColorWheel->Controls->Add(this->buttonSaveColor);
			this->tabPageColorWheel->Controls->Add(this->labelColorVMax);
			this->tabPageColorWheel->Controls->Add(this->labelColorSMax);
			this->tabPageColorWheel->Controls->Add(this->labelColorHMax);
			this->tabPageColorWheel->Controls->Add(this->labelColorVi);
			this->tabPageColorWheel->Controls->Add(this->labelColorSi);
			this->tabPageColorWheel->Controls->Add(this->labelColorHi);
			this->tabPageColorWheel->Controls->Add(this->labelColorVMin);
			this->tabPageColorWheel->Controls->Add(this->labelColorVName);
			this->tabPageColorWheel->Controls->Add(this->labelColorVMove);
			this->tabPageColorWheel->Controls->Add(this->labelColorSMove);
			this->tabPageColorWheel->Controls->Add(this->labelColorVMoveName);
			this->tabPageColorWheel->Controls->Add(this->labelColorSMin);
			this->tabPageColorWheel->Controls->Add(this->labelColorSMoveName);
			this->tabPageColorWheel->Controls->Add(this->labelColorSName);
			this->tabPageColorWheel->Controls->Add(this->labelColorHMove);
			this->tabPageColorWheel->Controls->Add(this->labelColorHMoveName);
			this->tabPageColorWheel->Controls->Add(this->labelColorHMin);
			this->tabPageColorWheel->Controls->Add(this->labelColorHName);
			this->tabPageColorWheel->Controls->Add(this->pictureBoxGrayLevel);
			this->tabPageColorWheel->Controls->Add(this->pictureBoxColorWheel);
			this->tabPageColorWheel->Location = System::Drawing::Point(4, 22);
			this->tabPageColorWheel->Name = L"tabPageColorWheel";
			this->tabPageColorWheel->Padding = System::Windows::Forms::Padding(3);
			this->tabPageColorWheel->Size = System::Drawing::Size(221, 238);
			this->tabPageColorWheel->TabIndex = 1;
			this->tabPageColorWheel->Text = L"Color Wheel";
			// 
			// buttonLoadColor
			// 
			this->buttonLoadColor->Location = System::Drawing::Point(167, 187);
			this->buttonLoadColor->Name = L"buttonLoadColor";
			this->buttonLoadColor->Size = System::Drawing::Size(40, 23);
			this->buttonLoadColor->TabIndex = 48;
			this->buttonLoadColor->Text = L"Load";
			this->buttonLoadColor->UseVisualStyleBackColor = true;
			this->buttonLoadColor->Click += gcnew System::EventHandler(this, &Form1::buttonLoadColor_Click);
			// 
			// buttonSaveColor
			// 
			this->buttonSaveColor->Location = System::Drawing::Point(167, 212);
			this->buttonSaveColor->Name = L"buttonSaveColor";
			this->buttonSaveColor->Size = System::Drawing::Size(40, 23);
			this->buttonSaveColor->TabIndex = 48;
			this->buttonSaveColor->Text = L"Save";
			this->buttonSaveColor->UseVisualStyleBackColor = true;
			this->buttonSaveColor->Click += gcnew System::EventHandler(this, &Form1::buttonSaveColor_Click);
			// 
			// labelColorVMax
			// 
			this->labelColorVMax->AutoSize = true;
			this->labelColorVMax->Location = System::Drawing::Point(61, 220);
			this->labelColorVMax->Name = L"labelColorVMax";
			this->labelColorVMax->Size = System::Drawing::Size(29, 12);
			this->labelColorVMax->TabIndex = 44;
			this->labelColorVMax->Text = L"XXX";
			// 
			// labelColorSMax
			// 
			this->labelColorSMax->AutoSize = true;
			this->labelColorSMax->Location = System::Drawing::Point(61, 205);
			this->labelColorSMax->Name = L"labelColorSMax";
			this->labelColorSMax->Size = System::Drawing::Size(29, 12);
			this->labelColorSMax->TabIndex = 43;
			this->labelColorSMax->Text = L"XXX";
			// 
			// labelColorHMax
			// 
			this->labelColorHMax->AutoSize = true;
			this->labelColorHMax->Location = System::Drawing::Point(61, 190);
			this->labelColorHMax->Name = L"labelColorHMax";
			this->labelColorHMax->Size = System::Drawing::Size(29, 12);
			this->labelColorHMax->TabIndex = 42;
			this->labelColorHMax->Text = L"XXX";
			// 
			// labelColorVi
			// 
			this->labelColorVi->AutoSize = true;
			this->labelColorVi->Location = System::Drawing::Point(50, 220);
			this->labelColorVi->Name = L"labelColorVi";
			this->labelColorVi->Size = System::Drawing::Size(11, 12);
			this->labelColorVi->TabIndex = 47;
			this->labelColorVi->Text = L"~";
			// 
			// labelColorSi
			// 
			this->labelColorSi->AutoSize = true;
			this->labelColorSi->Location = System::Drawing::Point(50, 205);
			this->labelColorSi->Name = L"labelColorSi";
			this->labelColorSi->Size = System::Drawing::Size(11, 12);
			this->labelColorSi->TabIndex = 46;
			this->labelColorSi->Text = L"~";
			// 
			// labelColorHi
			// 
			this->labelColorHi->AutoSize = true;
			this->labelColorHi->Location = System::Drawing::Point(50, 190);
			this->labelColorHi->Name = L"labelColorHi";
			this->labelColorHi->Size = System::Drawing::Size(11, 12);
			this->labelColorHi->TabIndex = 45;
			this->labelColorHi->Text = L"~";
			// 
			// labelColorVMin
			// 
			this->labelColorVMin->AutoSize = true;
			this->labelColorVMin->Location = System::Drawing::Point(25, 220);
			this->labelColorVMin->Name = L"labelColorVMin";
			this->labelColorVMin->Size = System::Drawing::Size(29, 12);
			this->labelColorVMin->TabIndex = 38;
			this->labelColorVMin->Text = L"XXX";
			// 
			// labelColorVName
			// 
			this->labelColorVName->AutoSize = true;
			this->labelColorVName->Location = System::Drawing::Point(7, 220);
			this->labelColorVName->Name = L"labelColorVName";
			this->labelColorVName->Size = System::Drawing::Size(19, 12);
			this->labelColorVName->TabIndex = 37;
			this->labelColorVName->Text = L"V :";
			// 
			// labelColorVMove
			// 
			this->labelColorVMove->AutoSize = true;
			this->labelColorVMove->Location = System::Drawing::Point(136, 220);
			this->labelColorVMove->Name = L"labelColorVMove";
			this->labelColorVMove->Size = System::Drawing::Size(29, 12);
			this->labelColorVMove->TabIndex = 36;
			this->labelColorVMove->Text = L"XXX";
			// 
			// labelColorSMove
			// 
			this->labelColorSMove->AutoSize = true;
			this->labelColorSMove->Location = System::Drawing::Point(136, 205);
			this->labelColorSMove->Name = L"labelColorSMove";
			this->labelColorSMove->Size = System::Drawing::Size(29, 12);
			this->labelColorSMove->TabIndex = 36;
			this->labelColorSMove->Text = L"XXX";
			// 
			// labelColorVMoveName
			// 
			this->labelColorVMoveName->AutoSize = true;
			this->labelColorVMoveName->Location = System::Drawing::Point(90, 220);
			this->labelColorVMoveName->Name = L"labelColorVMoveName";
			this->labelColorVMoveName->Size = System::Drawing::Size(49, 12);
			this->labelColorVMoveName->TabIndex = 41;
			this->labelColorVMoveName->Text = L"Move V :";
			this->labelColorVMoveName->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// labelColorSMin
			// 
			this->labelColorSMin->AutoSize = true;
			this->labelColorSMin->Location = System::Drawing::Point(25, 205);
			this->labelColorSMin->Name = L"labelColorSMin";
			this->labelColorSMin->Size = System::Drawing::Size(29, 12);
			this->labelColorSMin->TabIndex = 36;
			this->labelColorSMin->Text = L"XXX";
			// 
			// labelColorSMoveName
			// 
			this->labelColorSMoveName->AutoSize = true;
			this->labelColorSMoveName->Location = System::Drawing::Point(91, 205);
			this->labelColorSMoveName->Name = L"labelColorSMoveName";
			this->labelColorSMoveName->Size = System::Drawing::Size(47, 12);
			this->labelColorSMoveName->TabIndex = 41;
			this->labelColorSMoveName->Text = L"Move S :";
			this->labelColorSMoveName->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// labelColorSName
			// 
			this->labelColorSName->AutoSize = true;
			this->labelColorSName->Location = System::Drawing::Point(8, 205);
			this->labelColorSName->Name = L"labelColorSName";
			this->labelColorSName->Size = System::Drawing::Size(17, 12);
			this->labelColorSName->TabIndex = 41;
			this->labelColorSName->Text = L"S :";
			this->labelColorSName->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// labelColorHMove
			// 
			this->labelColorHMove->AutoSize = true;
			this->labelColorHMove->Location = System::Drawing::Point(136, 190);
			this->labelColorHMove->Name = L"labelColorHMove";
			this->labelColorHMove->Size = System::Drawing::Size(29, 12);
			this->labelColorHMove->TabIndex = 40;
			this->labelColorHMove->Text = L"XXX";
			// 
			// labelColorHMoveName
			// 
			this->labelColorHMoveName->AutoSize = true;
			this->labelColorHMoveName->Location = System::Drawing::Point(90, 190);
			this->labelColorHMoveName->Name = L"labelColorHMoveName";
			this->labelColorHMoveName->Size = System::Drawing::Size(49, 12);
			this->labelColorHMoveName->TabIndex = 39;
			this->labelColorHMoveName->Text = L"Move H :";
			// 
			// labelColorHMin
			// 
			this->labelColorHMin->AutoSize = true;
			this->labelColorHMin->Location = System::Drawing::Point(25, 190);
			this->labelColorHMin->Name = L"labelColorHMin";
			this->labelColorHMin->Size = System::Drawing::Size(29, 12);
			this->labelColorHMin->TabIndex = 40;
			this->labelColorHMin->Text = L"XXX";
			// 
			// labelColorHName
			// 
			this->labelColorHName->AutoSize = true;
			this->labelColorHName->Location = System::Drawing::Point(7, 190);
			this->labelColorHName->Name = L"labelColorHName";
			this->labelColorHName->Size = System::Drawing::Size(19, 12);
			this->labelColorHName->TabIndex = 39;
			this->labelColorHName->Text = L"H :";
			// 
			// pictureBoxGrayLevel
			// 
			this->pictureBoxGrayLevel->BackColor = System::Drawing::Color::Gainsboro;
			this->pictureBoxGrayLevel->Location = System::Drawing::Point(190, 4);
			this->pictureBoxGrayLevel->Name = L"pictureBoxGrayLevel";
			this->pictureBoxGrayLevel->Size = System::Drawing::Size(26, 181);
			this->pictureBoxGrayLevel->TabIndex = 0;
			this->pictureBoxGrayLevel->TabStop = false;
			this->pictureBoxGrayLevel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxGrayLevel_MouseDown);
			this->pictureBoxGrayLevel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxGrayLevel_MouseMove);
			this->pictureBoxGrayLevel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxGrayLevel_MouseUp);
			// 
			// pictureBoxColorWheel
			// 
			this->pictureBoxColorWheel->BackColor = System::Drawing::Color::Gainsboro;
			this->pictureBoxColorWheel->Location = System::Drawing::Point(4, 4);
			this->pictureBoxColorWheel->Name = L"pictureBoxColorWheel";
			this->pictureBoxColorWheel->Size = System::Drawing::Size(181, 181);
			this->pictureBoxColorWheel->TabIndex = 0;
			this->pictureBoxColorWheel->TabStop = false;
			this->pictureBoxColorWheel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxColorWheel_MouseDown);
			this->pictureBoxColorWheel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxColorWheel_MouseMove);
			this->pictureBoxColorWheel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBoxColorWheel_MouseUp);
			// 
			// tabPageScrollBar
			// 
			this->tabPageScrollBar->BackColor = System::Drawing::Color::Gainsboro;
			this->tabPageScrollBar->Controls->Add(this->buttonLoadColor2);
			this->tabPageScrollBar->Controls->Add(this->buttonSaveColor2);
			this->tabPageScrollBar->Controls->Add(this->textBoxColor3Max);
			this->tabPageScrollBar->Controls->Add(this->textBoxColor3Min);
			this->tabPageScrollBar->Controls->Add(this->textBoxColor2Max);
			this->tabPageScrollBar->Controls->Add(this->textBoxColor2Min);
			this->tabPageScrollBar->Controls->Add(this->textBoxColor1Max);
			this->tabPageScrollBar->Controls->Add(this->textBoxColor1Min);
			this->tabPageScrollBar->Controls->Add(this->hScrollBarColor3Max);
			this->tabPageScrollBar->Controls->Add(this->hScrollBarColor3Min);
			this->tabPageScrollBar->Controls->Add(this->hScrollBarColor2Max);
			this->tabPageScrollBar->Controls->Add(this->hScrollBarColor2Min);
			this->tabPageScrollBar->Controls->Add(this->hScrollBarColor1Max);
			this->tabPageScrollBar->Controls->Add(this->hScrollBarColor1Min);
			this->tabPageScrollBar->Location = System::Drawing::Point(4, 22);
			this->tabPageScrollBar->Name = L"tabPageScrollBar";
			this->tabPageScrollBar->Padding = System::Windows::Forms::Padding(3);
			this->tabPageScrollBar->Size = System::Drawing::Size(221, 238);
			this->tabPageScrollBar->TabIndex = 0;
			this->tabPageScrollBar->Text = L"Scroll Bar";
			// 
			// buttonLoadColor2
			// 
			this->buttonLoadColor2->Location = System::Drawing::Point(105, 167);
			this->buttonLoadColor2->Name = L"buttonLoadColor2";
			this->buttonLoadColor2->Size = System::Drawing::Size(75, 23);
			this->buttonLoadColor2->TabIndex = 32;
			this->buttonLoadColor2->Text = L"LoadColor";
			this->buttonLoadColor2->UseVisualStyleBackColor = true;
			// 
			// buttonSaveColor2
			// 
			this->buttonSaveColor2->Location = System::Drawing::Point(22, 167);
			this->buttonSaveColor2->Name = L"buttonSaveColor2";
			this->buttonSaveColor2->Size = System::Drawing::Size(75, 23);
			this->buttonSaveColor2->TabIndex = 31;
			this->buttonSaveColor2->Text = L"SaveColor";
			this->buttonSaveColor2->UseVisualStyleBackColor = true;
			// 
			// textBoxColor3Max
			// 
			this->textBoxColor3Max->Location = System::Drawing::Point(183, 128);
			this->textBoxColor3Max->Name = L"textBoxColor3Max";
			this->textBoxColor3Max->Size = System::Drawing::Size(32, 22);
			this->textBoxColor3Max->TabIndex = 30;
			this->textBoxColor3Max->Text = L"255";
			this->textBoxColor3Max->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxColor3Min
			// 
			this->textBoxColor3Min->Location = System::Drawing::Point(11, 116);
			this->textBoxColor3Min->Name = L"textBoxColor3Min";
			this->textBoxColor3Min->Size = System::Drawing::Size(32, 22);
			this->textBoxColor3Min->TabIndex = 29;
			this->textBoxColor3Min->Text = L"0";
			this->textBoxColor3Min->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxColor2Max
			// 
			this->textBoxColor2Max->Location = System::Drawing::Point(183, 87);
			this->textBoxColor2Max->Name = L"textBoxColor2Max";
			this->textBoxColor2Max->Size = System::Drawing::Size(32, 22);
			this->textBoxColor2Max->TabIndex = 28;
			this->textBoxColor2Max->Text = L"255";
			this->textBoxColor2Max->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxColor2Min
			// 
			this->textBoxColor2Min->Location = System::Drawing::Point(11, 70);
			this->textBoxColor2Min->Name = L"textBoxColor2Min";
			this->textBoxColor2Min->Size = System::Drawing::Size(32, 22);
			this->textBoxColor2Min->TabIndex = 27;
			this->textBoxColor2Min->Text = L"0";
			this->textBoxColor2Min->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxColor1Max
			// 
			this->textBoxColor1Max->Location = System::Drawing::Point(183, 40);
			this->textBoxColor1Max->Name = L"textBoxColor1Max";
			this->textBoxColor1Max->Size = System::Drawing::Size(32, 22);
			this->textBoxColor1Max->TabIndex = 26;
			this->textBoxColor1Max->Text = L"255";
			this->textBoxColor1Max->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxColor1Min
			// 
			this->textBoxColor1Min->Location = System::Drawing::Point(11, 23);
			this->textBoxColor1Min->Name = L"textBoxColor1Min";
			this->textBoxColor1Min->Size = System::Drawing::Size(32, 22);
			this->textBoxColor1Min->TabIndex = 25;
			this->textBoxColor1Min->Text = L"0";
			this->textBoxColor1Min->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// hScrollBarColor3Max
			// 
			this->hScrollBarColor3Max->LargeChange = 1;
			this->hScrollBarColor3Max->Location = System::Drawing::Point(46, 133);
			this->hScrollBarColor3Max->Maximum = 255;
			this->hScrollBarColor3Max->Name = L"hScrollBarColor3Max";
			this->hScrollBarColor3Max->Size = System::Drawing::Size(134, 17);
			this->hScrollBarColor3Max->TabIndex = 24;
			this->hScrollBarColor3Max->Value = 255;
			// 
			// hScrollBarColor3Min
			// 
			this->hScrollBarColor3Min->LargeChange = 1;
			this->hScrollBarColor3Min->Location = System::Drawing::Point(46, 116);
			this->hScrollBarColor3Min->Maximum = 255;
			this->hScrollBarColor3Min->Name = L"hScrollBarColor3Min";
			this->hScrollBarColor3Min->Size = System::Drawing::Size(134, 17);
			this->hScrollBarColor3Min->TabIndex = 23;
			// 
			// hScrollBarColor2Max
			// 
			this->hScrollBarColor2Max->LargeChange = 1;
			this->hScrollBarColor2Max->Location = System::Drawing::Point(46, 87);
			this->hScrollBarColor2Max->Maximum = 255;
			this->hScrollBarColor2Max->Name = L"hScrollBarColor2Max";
			this->hScrollBarColor2Max->Size = System::Drawing::Size(134, 17);
			this->hScrollBarColor2Max->TabIndex = 22;
			this->hScrollBarColor2Max->Value = 255;
			// 
			// hScrollBarColor2Min
			// 
			this->hScrollBarColor2Min->LargeChange = 1;
			this->hScrollBarColor2Min->Location = System::Drawing::Point(46, 70);
			this->hScrollBarColor2Min->Maximum = 255;
			this->hScrollBarColor2Min->Name = L"hScrollBarColor2Min";
			this->hScrollBarColor2Min->Size = System::Drawing::Size(134, 17);
			this->hScrollBarColor2Min->TabIndex = 21;
			// 
			// hScrollBarColor1Max
			// 
			this->hScrollBarColor1Max->LargeChange = 1;
			this->hScrollBarColor1Max->Location = System::Drawing::Point(46, 40);
			this->hScrollBarColor1Max->Maximum = 255;
			this->hScrollBarColor1Max->Name = L"hScrollBarColor1Max";
			this->hScrollBarColor1Max->Size = System::Drawing::Size(134, 17);
			this->hScrollBarColor1Max->TabIndex = 20;
			this->hScrollBarColor1Max->Value = 255;
			// 
			// hScrollBarColor1Min
			// 
			this->hScrollBarColor1Min->LargeChange = 1;
			this->hScrollBarColor1Min->Location = System::Drawing::Point(46, 23);
			this->hScrollBarColor1Min->Maximum = 255;
			this->hScrollBarColor1Min->Name = L"hScrollBarColor1Min";
			this->hScrollBarColor1Min->Size = System::Drawing::Size(134, 17);
			this->hScrollBarColor1Min->TabIndex = 19;
			// 
			// radioButtonObject1
			// 
			this->radioButtonObject1->AutoSize = true;
			this->radioButtonObject1->Checked = true;
			this->radioButtonObject1->Location = System::Drawing::Point(16, 17);
			this->radioButtonObject1->Name = L"radioButtonObject1";
			this->radioButtonObject1->Size = System::Drawing::Size(77, 16);
			this->radioButtonObject1->TabIndex = 33;
			this->radioButtonObject1->TabStop = true;
			this->radioButtonObject1->Text = L"Eye Pupil";
			this->radioButtonObject1->UseVisualStyleBackColor = true;
			this->radioButtonObject1->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonObj_CheckedChanged);
			// 
			// radioButtonObject2
			// 
			this->radioButtonObject2->AutoSize = true;
			this->radioButtonObject2->Location = System::Drawing::Point(16, 36);
			this->radioButtonObject2->Name = L"radioButtonObject2";
			this->radioButtonObject2->Size = System::Drawing::Size(81, 16);
			this->radioButtonObject2->TabIndex = 34;
			this->radioButtonObject2->Text = L"Eye White";
			this->radioButtonObject2->UseVisualStyleBackColor = true;
			this->radioButtonObject2->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonObj_CheckedChanged);
			// 
			// radioButtonObject4
			// 
			this->radioButtonObject4->AutoSize = true;
			this->radioButtonObject4->Location = System::Drawing::Point(16, 69);
			this->radioButtonObject4->Name = L"radioButtonObject4";
			this->radioButtonObject4->Size = System::Drawing::Size(52, 16);
			this->radioButtonObject4->TabIndex = 36;
			this->radioButtonObject4->Text = L"None";
			this->radioButtonObject4->UseVisualStyleBackColor = true;
			this->radioButtonObject4->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonObj_CheckedChanged);
			// 
			// radioButtonObject3
			// 
			this->radioButtonObject3->AutoSize = true;
			this->radioButtonObject3->Location = System::Drawing::Point(16, 53);
			this->radioButtonObject3->Name = L"radioButtonObject3";
			this->radioButtonObject3->Size = System::Drawing::Size(72, 16);
			this->radioButtonObject3->TabIndex = 35;
			this->radioButtonObject3->Text = L"Eye Lids";
			this->radioButtonObject3->UseVisualStyleBackColor = true;
			this->radioButtonObject3->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonObj_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButtonObject1);
			this->groupBox1->Controls->Add(this->radioButtonObject4);
			this->groupBox1->Controls->Add(this->radioButtonObject2);
			this->groupBox1->Controls->Add(this->radioButtonObject3);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->groupBox1->Location = System::Drawing::Point(389, 447);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(129, 92);
			this->groupBox1->TabIndex = 37;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Object";
			// 
			// buttonRunStrategy
			// 
			this->buttonRunStrategy->BackColor = System::Drawing::SystemColors::Control;
			this->buttonRunStrategy->Enabled = false;
			this->buttonRunStrategy->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->buttonRunStrategy->Location = System::Drawing::Point(640, 385);
			this->buttonRunStrategy->Name = L"buttonRunStrategy";
			this->buttonRunStrategy->Size = System::Drawing::Size(110, 50);
			this->buttonRunStrategy->TabIndex = 38;
			this->buttonRunStrategy->Text = L"Run Strategy";
			this->buttonRunStrategy->UseVisualStyleBackColor = false;
			this->buttonRunStrategy->Click += gcnew System::EventHandler(this, &Form1::buttonRunStrategy_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(91, 12);
			this->label2->TabIndex = 41;
			this->label2->Text = L"FaceRegion X :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(10, 53);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 12);
			this->label3->TabIndex = 42;
			this->label3->Text = L"FaceRegion Y :";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(10, 81);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(91, 12);
			this->label4->TabIndex = 43;
			this->label4->Text = L"FaceRegion H :";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(10, 109);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(90, 12);
			this->label5->TabIndex = 44;
			this->label5->Text = L"FaceRegion W:";
			// 
			// textBox_FaceRegionX
			// 
			this->textBox_FaceRegionX->Location = System::Drawing::Point(104, 21);
			this->textBox_FaceRegionX->Name = L"textBox_FaceRegionX";
			this->textBox_FaceRegionX->Size = System::Drawing::Size(40, 22);
			this->textBox_FaceRegionX->TabIndex = 45;
			this->textBox_FaceRegionX->Text = L"90";
			this->textBox_FaceRegionX->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox_FaceRegionY
			// 
			this->textBox_FaceRegionY->Location = System::Drawing::Point(104, 49);
			this->textBox_FaceRegionY->Name = L"textBox_FaceRegionY";
			this->textBox_FaceRegionY->Size = System::Drawing::Size(40, 22);
			this->textBox_FaceRegionY->TabIndex = 46;
			this->textBox_FaceRegionY->Text = L"5";
			this->textBox_FaceRegionY->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox_FaceRegionHeight
			// 
			this->textBox_FaceRegionHeight->Location = System::Drawing::Point(104, 77);
			this->textBox_FaceRegionHeight->Name = L"textBox_FaceRegionHeight";
			this->textBox_FaceRegionHeight->Size = System::Drawing::Size(40, 22);
			this->textBox_FaceRegionHeight->TabIndex = 47;
			this->textBox_FaceRegionHeight->Text = L"200";
			this->textBox_FaceRegionHeight->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox_FaceRegionWidth
			// 
			this->textBox_FaceRegionWidth->Location = System::Drawing::Point(104, 105);
			this->textBox_FaceRegionWidth->Name = L"textBox_FaceRegionWidth";
			this->textBox_FaceRegionWidth->Size = System::Drawing::Size(40, 22);
			this->textBox_FaceRegionWidth->TabIndex = 48;
			this->textBox_FaceRegionWidth->Text = L"200";
			this->textBox_FaceRegionWidth->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox_FaceRegionX);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->textBox_FaceRegionWidth);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->textBox_FaceRegionHeight);
			this->groupBox2->Controls->Add(this->textBox_FaceRegionY);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->groupBox2->Location = System::Drawing::Point(16, 21);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(152, 137);
			this->groupBox2->TabIndex = 49;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Face Region";
			// 
			// buttonApply
			// 
			this->buttonApply->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->buttonApply->Location = System::Drawing::Point(255, 135);
			this->buttonApply->Name = L"buttonApply";
			this->buttonApply->Size = System::Drawing::Size(75, 32);
			this->buttonApply->TabIndex = 50;
			this->buttonApply->Text = L"Apply";
			this->buttonApply->UseVisualStyleBackColor = true;
			this->buttonApply->Click += gcnew System::EventHandler(this, &Form1::buttonApply_Click);
			// 
			// buttonDetectEyeRegion
			// 
			this->buttonDetectEyeRegion->BackColor = System::Drawing::SystemColors::Control;
			this->buttonDetectEyeRegion->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->buttonDetectEyeRegion->Location = System::Drawing::Point(524, 329);
			this->buttonDetectEyeRegion->Name = L"buttonDetectEyeRegion";
			this->buttonDetectEyeRegion->Size = System::Drawing::Size(110, 50);
			this->buttonDetectEyeRegion->TabIndex = 51;
			this->buttonDetectEyeRegion->Text = L"Detect eye region";
			this->buttonDetectEyeRegion->UseVisualStyleBackColor = false;
			this->buttonDetectEyeRegion->Click += gcnew System::EventHandler(this, &Form1::buttonDetectEyeRegion_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(193, 107);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(86, 12);
			this->label6->TabIndex = 49;
			this->label6->Text = L"eye gray TH : ";
			// 
			// textBox_EyeGaryTH
			// 
			this->textBox_EyeGaryTH->Location = System::Drawing::Point(282, 103);
			this->textBox_EyeGaryTH->Name = L"textBox_EyeGaryTH";
			this->textBox_EyeGaryTH->Size = System::Drawing::Size(40, 22);
			this->textBox_EyeGaryTH->TabIndex = 50;
			this->textBox_EyeGaryTH->Text = L"32";
			this->textBox_EyeGaryTH->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// labelVision_DAnumbers
			// 
			this->labelVision_DAnumbers->AutoSize = true;
			this->labelVision_DAnumbers->Location = System::Drawing::Point(314, 67);
			this->labelVision_DAnumbers->Name = L"labelVision_DAnumbers";
			this->labelVision_DAnumbers->Size = System::Drawing::Size(23, 12);
			this->labelVision_DAnumbers->TabIndex = 57;
			this->labelVision_DAnumbers->Text = L"2.5";
			// 
			// labelVision_EDnumbers
			// 
			this->labelVision_EDnumbers->AutoSize = true;
			this->labelVision_EDnumbers->Location = System::Drawing::Point(315, 28);
			this->labelVision_EDnumbers->Name = L"labelVision_EDnumbers";
			this->labelVision_EDnumbers->Size = System::Drawing::Size(12, 12);
			this->labelVision_EDnumbers->TabIndex = 56;
			this->labelVision_EDnumbers->Text = L"1";
			// 
			// label78
			// 
			this->label78->AutoSize = true;
			this->label78->Location = System::Drawing::Point(281, 68);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(34, 12);
			this->label78->TabIndex = 55;
			this->label78->Text = L"DA =";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(281, 27);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(33, 12);
			this->label7->TabIndex = 54;
			this->label7->Text = L"ED =";
			// 
			// trackBarVision_DA
			// 
			this->trackBarVision_DA->Location = System::Drawing::Point(185, 66);
			this->trackBarVision_DA->Maximum = 50;
			this->trackBarVision_DA->Name = L"trackBarVision_DA";
			this->trackBarVision_DA->Size = System::Drawing::Size(94, 45);
			this->trackBarVision_DA->TabIndex = 53;
			this->trackBarVision_DA->Value = 25;
			this->trackBarVision_DA->Scroll += gcnew System::EventHandler(this, &Form1::trackBarVision_DA_Scroll);
			// 
			// trackBarVision_ED
			// 
			this->trackBarVision_ED->Location = System::Drawing::Point(185, 22);
			this->trackBarVision_ED->Maximum = 50;
			this->trackBarVision_ED->Name = L"trackBarVision_ED";
			this->trackBarVision_ED->Size = System::Drawing::Size(94, 45);
			this->trackBarVision_ED->TabIndex = 52;
			this->trackBarVision_ED->Value = 10;
			this->trackBarVision_ED->Scroll += gcnew System::EventHandler(this, &Form1::trackBarVision_ED_Scroll);
			// 
			// groupBoxRx
			// 
			this->groupBoxRx->Controls->Add(this->labelSensorMagAzimuth);
			this->groupBoxRx->Controls->Add(this->label12);
			this->groupBoxRx->Controls->Add(this->labelRxBodyDoing);
			this->groupBoxRx->Controls->Add(this->label8);
			this->groupBoxRx->Controls->Add(this->labelRxPanPosAng);
			this->groupBoxRx->Controls->Add(this->label35);
			this->groupBoxRx->Controls->Add(this->labelRxPanPos);
			this->groupBoxRx->Controls->Add(this->label10);
			this->groupBoxRx->Controls->Add(this->labelRxTiltPosAng);
			this->groupBoxRx->Controls->Add(this->label39);
			this->groupBoxRx->Controls->Add(this->label33);
			this->groupBoxRx->Controls->Add(this->labelRxTiltPos);
			this->groupBoxRx->Controls->Add(this->label11);
			this->groupBoxRx->Controls->Add(this->labelRxDipBinary3);
			this->groupBoxRx->Controls->Add(this->labelRxDipBinary5);
			this->groupBoxRx->Controls->Add(this->labelRxDipBinary0);
			this->groupBoxRx->Controls->Add(this->labelRxDipBinary1);
			this->groupBoxRx->Controls->Add(this->labelRxDipBinary2);
			this->groupBoxRx->Controls->Add(this->labelRxDipBinary4);
			this->groupBoxRx->Controls->Add(this->labelRxDip);
			this->groupBoxRx->Controls->Add(this->label13);
			this->groupBoxRx->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold));
			this->groupBoxRx->Location = System::Drawing::Point(12, 268);
			this->groupBoxRx->Name = L"groupBoxRx";
			this->groupBoxRx->Size = System::Drawing::Size(155, 116);
			this->groupBoxRx->TabIndex = 71;
			this->groupBoxRx->TabStop = false;
			this->groupBoxRx->Text = L"Rx";
			// 
			// labelSensorMagAzimuth
			// 
			this->labelSensorMagAzimuth->AutoSize = true;
			this->labelSensorMagAzimuth->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelSensorMagAzimuth->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelSensorMagAzimuth->Location = System::Drawing::Point(91, 94);
			this->labelSensorMagAzimuth->Name = L"labelSensorMagAzimuth";
			this->labelSensorMagAzimuth->Size = System::Drawing::Size(11, 12);
			this->labelSensorMagAzimuth->TabIndex = 11;
			this->labelSensorMagAzimuth->Text = L"x";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label12->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label12->Location = System::Drawing::Point(6, 94);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(59, 12);
			this->label12->TabIndex = 10;
			this->label12->Text = L"RxAzimuth";
			// 
			// labelRxBodyDoing
			// 
			this->labelRxBodyDoing->AutoSize = true;
			this->labelRxBodyDoing->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxBodyDoing->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxBodyDoing->Location = System::Drawing::Point(91, 74);
			this->labelRxBodyDoing->Name = L"labelRxBodyDoing";
			this->labelRxBodyDoing->Size = System::Drawing::Size(11, 12);
			this->labelRxBodyDoing->TabIndex = 9;
			this->labelRxBodyDoing->Text = L"x";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label8->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label8->Location = System::Drawing::Point(6, 74);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(74, 12);
			this->label8->TabIndex = 8;
			this->label8->Text = L"RxBodyDoing";
			// 
			// labelRxPanPosAng
			// 
			this->labelRxPanPosAng->AutoSize = true;
			this->labelRxPanPosAng->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxPanPosAng->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxPanPosAng->Location = System::Drawing::Point(129, 56);
			this->labelRxPanPosAng->Name = L"labelRxPanPosAng";
			this->labelRxPanPosAng->Size = System::Drawing::Size(17, 12);
			this->labelRxPanPosAng->TabIndex = 5;
			this->labelRxPanPosAng->Text = L"xx";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label35->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label35->Location = System::Drawing::Point(118, 57);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(8, 12);
			this->label35->TabIndex = 5;
			this->label35->Text = L"/";
			// 
			// labelRxPanPos
			// 
			this->labelRxPanPos->AutoSize = true;
			this->labelRxPanPos->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxPanPos->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxPanPos->Location = System::Drawing::Point(91, 56);
			this->labelRxPanPos->Name = L"labelRxPanPos";
			this->labelRxPanPos->Size = System::Drawing::Size(11, 12);
			this->labelRxPanPos->TabIndex = 5;
			this->labelRxPanPos->Text = L"x";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label10->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label10->Location = System::Drawing::Point(6, 56);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(52, 12);
			this->label10->TabIndex = 4;
			this->label10->Text = L"RxPanPos";
			// 
			// labelRxTiltPosAng
			// 
			this->labelRxTiltPosAng->AutoSize = true;
			this->labelRxTiltPosAng->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxTiltPosAng->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxTiltPosAng->Location = System::Drawing::Point(129, 36);
			this->labelRxTiltPosAng->Name = L"labelRxTiltPosAng";
			this->labelRxTiltPosAng->Size = System::Drawing::Size(17, 12);
			this->labelRxTiltPosAng->TabIndex = 3;
			this->labelRxTiltPosAng->Text = L"xx";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label39->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label39->Location = System::Drawing::Point(118, 18);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(8, 12);
			this->label39->TabIndex = 3;
			this->label39->Text = L"/";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label33->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label33->Location = System::Drawing::Point(118, 37);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(8, 12);
			this->label33->TabIndex = 3;
			this->label33->Text = L"/";
			// 
			// labelRxTiltPos
			// 
			this->labelRxTiltPos->AutoSize = true;
			this->labelRxTiltPos->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxTiltPos->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxTiltPos->Location = System::Drawing::Point(91, 36);
			this->labelRxTiltPos->Name = L"labelRxTiltPos";
			this->labelRxTiltPos->Size = System::Drawing::Size(11, 12);
			this->labelRxTiltPos->TabIndex = 3;
			this->labelRxTiltPos->Text = L"x";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label11->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label11->Location = System::Drawing::Point(6, 36);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(51, 12);
			this->label11->TabIndex = 2;
			this->label11->Text = L"RxTiltPos";
			// 
			// labelRxDipBinary3
			// 
			this->labelRxDipBinary3->AutoSize = true;
			this->labelRxDipBinary3->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxDipBinary3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxDipBinary3->Location = System::Drawing::Point(70, 19);
			this->labelRxDipBinary3->Name = L"labelRxDipBinary3";
			this->labelRxDipBinary3->Size = System::Drawing::Size(11, 12);
			this->labelRxDipBinary3->TabIndex = 1;
			this->labelRxDipBinary3->Text = L"x";
			// 
			// labelRxDipBinary5
			// 
			this->labelRxDipBinary5->AutoSize = true;
			this->labelRxDipBinary5->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxDipBinary5->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxDipBinary5->Location = System::Drawing::Point(48, 19);
			this->labelRxDipBinary5->Name = L"labelRxDipBinary5";
			this->labelRxDipBinary5->Size = System::Drawing::Size(11, 12);
			this->labelRxDipBinary5->TabIndex = 1;
			this->labelRxDipBinary5->Text = L"x";
			// 
			// labelRxDipBinary0
			// 
			this->labelRxDipBinary0->AutoSize = true;
			this->labelRxDipBinary0->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxDipBinary0->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxDipBinary0->Location = System::Drawing::Point(103, 19);
			this->labelRxDipBinary0->Name = L"labelRxDipBinary0";
			this->labelRxDipBinary0->Size = System::Drawing::Size(11, 12);
			this->labelRxDipBinary0->TabIndex = 1;
			this->labelRxDipBinary0->Text = L"x";
			// 
			// labelRxDipBinary1
			// 
			this->labelRxDipBinary1->AutoSize = true;
			this->labelRxDipBinary1->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxDipBinary1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxDipBinary1->Location = System::Drawing::Point(92, 19);
			this->labelRxDipBinary1->Name = L"labelRxDipBinary1";
			this->labelRxDipBinary1->Size = System::Drawing::Size(11, 12);
			this->labelRxDipBinary1->TabIndex = 1;
			this->labelRxDipBinary1->Text = L"x";
			// 
			// labelRxDipBinary2
			// 
			this->labelRxDipBinary2->AutoSize = true;
			this->labelRxDipBinary2->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxDipBinary2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxDipBinary2->Location = System::Drawing::Point(81, 19);
			this->labelRxDipBinary2->Name = L"labelRxDipBinary2";
			this->labelRxDipBinary2->Size = System::Drawing::Size(11, 12);
			this->labelRxDipBinary2->TabIndex = 1;
			this->labelRxDipBinary2->Text = L"x";
			// 
			// labelRxDipBinary4
			// 
			this->labelRxDipBinary4->AutoSize = true;
			this->labelRxDipBinary4->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxDipBinary4->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxDipBinary4->Location = System::Drawing::Point(59, 19);
			this->labelRxDipBinary4->Name = L"labelRxDipBinary4";
			this->labelRxDipBinary4->Size = System::Drawing::Size(11, 12);
			this->labelRxDipBinary4->TabIndex = 1;
			this->labelRxDipBinary4->Text = L"x";
			// 
			// labelRxDip
			// 
			this->labelRxDip->AutoSize = true;
			this->labelRxDip->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRxDip->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRxDip->Location = System::Drawing::Point(129, 18);
			this->labelRxDip->Name = L"labelRxDip";
			this->labelRxDip->Size = System::Drawing::Size(11, 12);
			this->labelRxDip->TabIndex = 1;
			this->labelRxDip->Text = L"x";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label13->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label13->Location = System::Drawing::Point(6, 18);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(36, 12);
			this->label13->TabIndex = 0;
			this->label13->Text = L"RxDip";
			// 
			// groupBoxTx
			// 
			this->groupBoxTx->Controls->Add(this->labelTxPanPosAng);
			this->groupBoxTx->Controls->Add(this->label31);
			this->groupBoxTx->Controls->Add(this->labelTxPanPos);
			this->groupBoxTx->Controls->Add(this->label14);
			this->groupBoxTx->Controls->Add(this->labelTxTiltPosAng);
			this->groupBoxTx->Controls->Add(this->label29);
			this->groupBoxTx->Controls->Add(this->labelTxTiltPos);
			this->groupBoxTx->Controls->Add(this->label15);
			this->groupBoxTx->Controls->Add(this->labelTxHeadMotion);
			this->groupBoxTx->Controls->Add(this->label16);
			this->groupBoxTx->Controls->Add(this->labelTxAngle);
			this->groupBoxTx->Controls->Add(this->label17);
			this->groupBoxTx->Controls->Add(this->labelTxDis);
			this->groupBoxTx->Controls->Add(this->label18);
			this->groupBoxTx->Controls->Add(this->labelTxBodyMotion);
			this->groupBoxTx->Controls->Add(this->label19);
			this->groupBoxTx->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold));
			this->groupBoxTx->Location = System::Drawing::Point(12, 390);
			this->groupBoxTx->Name = L"groupBoxTx";
			this->groupBoxTx->Size = System::Drawing::Size(155, 149);
			this->groupBoxTx->TabIndex = 72;
			this->groupBoxTx->TabStop = false;
			this->groupBoxTx->Text = L"Tx";
			// 
			// labelTxPanPosAng
			// 
			this->labelTxPanPosAng->AutoSize = true;
			this->labelTxPanPosAng->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxPanPosAng->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxPanPosAng->Location = System::Drawing::Point(126, 116);
			this->labelTxPanPosAng->Name = L"labelTxPanPosAng";
			this->labelTxPanPosAng->Size = System::Drawing::Size(17, 12);
			this->labelTxPanPosAng->TabIndex = 11;
			this->labelTxPanPosAng->Text = L"xx";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label31->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label31->Location = System::Drawing::Point(113, 117);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(8, 12);
			this->label31->TabIndex = 11;
			this->label31->Text = L"/";
			// 
			// labelTxPanPos
			// 
			this->labelTxPanPos->AutoSize = true;
			this->labelTxPanPos->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxPanPos->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxPanPos->Location = System::Drawing::Point(89, 116);
			this->labelTxPanPos->Name = L"labelTxPanPos";
			this->labelTxPanPos->Size = System::Drawing::Size(11, 12);
			this->labelTxPanPos->TabIndex = 11;
			this->labelTxPanPos->Text = L"x";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label14->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label14->Location = System::Drawing::Point(6, 116);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(51, 12);
			this->label14->TabIndex = 10;
			this->label14->Text = L"TxPanPos";
			// 
			// labelTxTiltPosAng
			// 
			this->labelTxTiltPosAng->AutoSize = true;
			this->labelTxTiltPosAng->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxTiltPosAng->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxTiltPosAng->Location = System::Drawing::Point(126, 96);
			this->labelTxTiltPosAng->Name = L"labelTxTiltPosAng";
			this->labelTxTiltPosAng->Size = System::Drawing::Size(17, 12);
			this->labelTxTiltPosAng->TabIndex = 9;
			this->labelTxTiltPosAng->Text = L"xx";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label29->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label29->Location = System::Drawing::Point(113, 97);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(8, 12);
			this->label29->TabIndex = 9;
			this->label29->Text = L"/";
			// 
			// labelTxTiltPos
			// 
			this->labelTxTiltPos->AutoSize = true;
			this->labelTxTiltPos->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxTiltPos->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxTiltPos->Location = System::Drawing::Point(89, 96);
			this->labelTxTiltPos->Name = L"labelTxTiltPos";
			this->labelTxTiltPos->Size = System::Drawing::Size(11, 12);
			this->labelTxTiltPos->TabIndex = 9;
			this->labelTxTiltPos->Text = L"x";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label15->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label15->Location = System::Drawing::Point(6, 96);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(50, 12);
			this->label15->TabIndex = 8;
			this->label15->Text = L"TxTiltPos";
			// 
			// labelTxHeadMotion
			// 
			this->labelTxHeadMotion->AutoSize = true;
			this->labelTxHeadMotion->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxHeadMotion->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxHeadMotion->Location = System::Drawing::Point(89, 76);
			this->labelTxHeadMotion->Name = L"labelTxHeadMotion";
			this->labelTxHeadMotion->Size = System::Drawing::Size(11, 12);
			this->labelTxHeadMotion->TabIndex = 7;
			this->labelTxHeadMotion->Text = L"x";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label16->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label16->Location = System::Drawing::Point(6, 76);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(76, 12);
			this->label16->TabIndex = 6;
			this->label16->Text = L"TxHeadMotion";
			// 
			// labelTxAngle
			// 
			this->labelTxAngle->AutoSize = true;
			this->labelTxAngle->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxAngle->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxAngle->Location = System::Drawing::Point(89, 56);
			this->labelTxAngle->Name = L"labelTxAngle";
			this->labelTxAngle->Size = System::Drawing::Size(11, 12);
			this->labelTxAngle->TabIndex = 5;
			this->labelTxAngle->Text = L"x";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label17->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label17->Location = System::Drawing::Point(6, 56);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(46, 12);
			this->label17->TabIndex = 4;
			this->label17->Text = L"TxAngle";
			// 
			// labelTxDis
			// 
			this->labelTxDis->AutoSize = true;
			this->labelTxDis->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxDis->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxDis->Location = System::Drawing::Point(89, 36);
			this->labelTxDis->Name = L"labelTxDis";
			this->labelTxDis->Size = System::Drawing::Size(11, 12);
			this->labelTxDis->TabIndex = 3;
			this->labelTxDis->Text = L"x";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label18->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label18->Location = System::Drawing::Point(6, 36);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(33, 12);
			this->label18->TabIndex = 2;
			this->label18->Text = L"TxDis";
			// 
			// labelTxBodyMotion
			// 
			this->labelTxBodyMotion->AutoSize = true;
			this->labelTxBodyMotion->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelTxBodyMotion->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelTxBodyMotion->Location = System::Drawing::Point(89, 16);
			this->labelTxBodyMotion->Name = L"labelTxBodyMotion";
			this->labelTxBodyMotion->Size = System::Drawing::Size(11, 12);
			this->labelTxBodyMotion->TabIndex = 1;
			this->labelTxBodyMotion->Text = L"x";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label19->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label19->Location = System::Drawing::Point(6, 16);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(78, 12);
			this->label19->TabIndex = 0;
			this->label19->Text = L"TxBodyMotion";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->groupBox2);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->labelVision_DAnumbers);
			this->groupBox3->Controls->Add(this->buttonApply);
			this->groupBox3->Controls->Add(this->labelVision_EDnumbers);
			this->groupBox3->Controls->Add(this->textBox_EyeGaryTH);
			this->groupBox3->Controls->Add(this->label78);
			this->groupBox3->Controls->Add(this->trackBarVision_ED);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->trackBarVision_DA);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->groupBox3->Location = System::Drawing::Point(174, 268);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(344, 173);
			this->groupBox3->TabIndex = 73;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Image Process TH";
			// 
			// serialPortRS232
			// 
			this->serialPortRS232->BaudRate = 115200;
			this->serialPortRS232->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Form1::serialPortRS232_DataReceived);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->labelRobotHeadSearchState);
			this->groupBox4->Controls->Add(this->labelRobotStableWait);
			this->groupBox4->Controls->Add(this->labelRelativeAzimuth);
			this->groupBox4->Controls->Add(this->label38);
			this->groupBox4->Controls->Add(this->label36);
			this->groupBox4->Controls->Add(this->label1);
			this->groupBox4->Controls->Add(this->label23);
			this->groupBox4->Controls->Add(this->labelIsBodyMotionDone);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold));
			this->groupBox4->Location = System::Drawing::Point(174, 447);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(209, 92);
			this->groupBox4->TabIndex = 79;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Strategy State";
			// 
			// labelRobotHeadSearchState
			// 
			this->labelRobotHeadSearchState->AutoSize = true;
			this->labelRobotHeadSearchState->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRobotHeadSearchState->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRobotHeadSearchState->Location = System::Drawing::Point(122, 71);
			this->labelRobotHeadSearchState->Name = L"labelRobotHeadSearchState";
			this->labelRobotHeadSearchState->Size = System::Drawing::Size(11, 12);
			this->labelRobotHeadSearchState->TabIndex = 10;
			this->labelRobotHeadSearchState->Text = L"x";
			// 
			// labelRobotStableWait
			// 
			this->labelRobotStableWait->AutoSize = true;
			this->labelRobotStableWait->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRobotStableWait->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRobotStableWait->Location = System::Drawing::Point(122, 54);
			this->labelRobotStableWait->Name = L"labelRobotStableWait";
			this->labelRobotStableWait->Size = System::Drawing::Size(11, 12);
			this->labelRobotStableWait->TabIndex = 10;
			this->labelRobotStableWait->Text = L"x";
			// 
			// labelRelativeAzimuth
			// 
			this->labelRelativeAzimuth->AutoSize = true;
			this->labelRelativeAzimuth->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelRelativeAzimuth->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelRelativeAzimuth->Location = System::Drawing::Point(122, 36);
			this->labelRelativeAzimuth->Name = L"labelRelativeAzimuth";
			this->labelRelativeAzimuth->Size = System::Drawing::Size(11, 12);
			this->labelRelativeAzimuth->TabIndex = 10;
			this->labelRelativeAzimuth->Text = L"x";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label38->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label38->Location = System::Drawing::Point(11, 71);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(61, 12);
			this->label38->TabIndex = 9;
			this->label38->Text = L"Search State";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label36->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label36->Location = System::Drawing::Point(11, 54);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(90, 12);
			this->label36->TabIndex = 9;
			this->label36->Text = L"Robot Stable Wait";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label1->Location = System::Drawing::Point(11, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(86, 12);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Relative Azimuth";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->label23->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label23->Location = System::Drawing::Point(11, 18);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(104, 12);
			this->label23->TabIndex = 7;
			this->label23->Text = L"Body Motion Done \?";
			// 
			// labelIsBodyMotionDone
			// 
			this->labelIsBodyMotionDone->AutoSize = true;
			this->labelIsBodyMotionDone->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->labelIsBodyMotionDone->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->labelIsBodyMotionDone->Location = System::Drawing::Point(122, 18);
			this->labelIsBodyMotionDone->Name = L"labelIsBodyMotionDone";
			this->labelIsBodyMotionDone->Size = System::Drawing::Size(11, 12);
			this->labelIsBodyMotionDone->TabIndex = 8;
			this->labelIsBodyMotionDone->Text = L"x";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackColor = System::Drawing::Color::Gainsboro;
			this->ClientSize = System::Drawing::Size(1000, 586);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBoxTx);
			this->Controls->Add(this->groupBoxRx);
			this->Controls->Add(this->buttonDetectEyeRegion);
			this->Controls->Add(this->buttonRunStrategy);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->tabControlColor);
			this->Controls->Add(this->buttonSetCam);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->buttonOpenCamTwo);
			this->Controls->Add(this->buttonOpenCamOne);
			this->Controls->Add(this->pictureBoxCamXtionInput);
			this->Controls->Add(this->pictureBoxGaze);
			this->Controls->Add(this->pictureBoxCamOneInput);
			this->Location = System::Drawing::Point(46, 23);
			this->Name = L"Form1";
			this->Padding = System::Windows::Forms::Padding(3);
			this->Text = L"GazeControl";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxCamOneInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxGaze))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxCamXtionInput))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tabControlColor->ResumeLayout(false);
			this->tabPageColorWheel->ResumeLayout(false);
			this->tabPageColorWheel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxGrayLevel))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxColorWheel))->EndInit();
			this->tabPageScrollBar->ResumeLayout(false);
			this->tabPageScrollBar->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarVision_DA))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarVision_ED))->EndInit();
			this->groupBoxRx->ResumeLayout(false);
			this->groupBoxRx->PerformLayout();
			this->groupBoxTx->ResumeLayout(false);
			this->groupBoxTx->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonOpenCamOne_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 //UI Setting
				 this->buttonOpenCamOne->Enabled = false;
				 this->buttonOpenCamTwo->Enabled = true;
				 this->buttonSetCam->Enabled = true;
				 this->buttonRunStrategy->Enabled = true;
				 
				 info->isCameraOpen = true;
				 //info->isXtionOpen = false;
				 //initial vision system
				 info->vision.initial();

				 //run backgroundWorker，且避免重複啟動 
				 if ( !this->backgroundWorkerCam1->IsBusy )
					 this->backgroundWorkerCam1->RunWorkerAsync();
			 }
private: System::Void buttonOpenCamTwo_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->myXtion = new XtionControl();
			 this->myXtion->Xtion_Init();

			 //UI Setting
			 this->buttonOpenCamTwo->Enabled = false;
			 info->isXtionOpen = true;

			 this->ColorImage = gcnew System::Drawing::Bitmap(640,480);
			 this->FinalImage = gcnew System::Drawing::Bitmap(640,480);
			 this->DepthImage = gcnew System::Drawing::Bitmap(320,240);
			 this->LastDepthImage = gcnew System::Drawing::Bitmap(320,240);
			 this->DepthViewBuffer = new unsigned char[320*240*3];

//           run backgroundWorker，且避免重複啟動 
// 			 if ( !this->backgroundWorkerCam2->IsBusy )
// 				 this->backgroundWorkerCam2->RunWorkerAsync();
		 }
private: System::Void backgroundWorkerCam1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

			 //跨執行緒處理，錯誤訊息不出現，但易造成介面上資料的不一致/損毀，不建議
			 //讓backgroundWorker 可以更新 UI
			 System::Windows::Forms::Form::CheckForIllegalCrossThreadCalls = false;

			 System::Diagnostics::Stopwatch^ frameWatch = gcnew System::Diagnostics::Stopwatch();

			 while(1)
			 {
				 Sleep(30);
				 try
				 {
					 /*------------------------ Image Process ----------------------------*/
					 //get image
					 if (info->isXtionOpen)
					 {
						 this->MainDisplay();
					 }
					 if ( info->isCameraOpen )
					 {
						 if ( info->vision.VI->isFrameNew(info->vision.camID) )	//ensure images are recursively obtained
						 {
							 info->vision.VI->getPixels( info->vision.camID ,(unsigned char*)info->vision.camFrame->imageData ,false ,true ); //for 320*240
							 //info->vision.VI->getPixels( info->vision.camID ,(unsigned char*)info->vision.camFrame->imageData ,false ,true ); //for 640*480
						 }
					 }

 					 //RGB -> HSV
 					 //cvCvtColor( info->vision.camFrame ,info->vision.camFrame_HSV ,CV_BGR2HSV_FULL );
 

// 
// 					 /*------------------------ Sensor information ----------------------------*/
// 
// 					 //compass
// 					 info->sensor.run();
 
 					 // Run Strategy
// 					 if( info->isStrategyRun )
// 					 {	
// 						 info->strategy.adult.run();
// 						 this->sendSerialData();
// 					 }

		
					 this->pictureBoxCamOneInput->Image = gcnew System::Drawing::Bitmap(
						 CAM_WIDTH,
						 CAM_HEIGHT,
						 CAM_WIDTH*3,
						 System::Drawing::Imaging::PixelFormat::Format24bppRgb,
						 System::IntPtr(info->vision.camFrame->imageData)
						 );

					 if ( info->vision.initialEyeRegion )
					 {
						 if ( !info->vision.isfindEye )//沒找到眼睛就重找
						 {
							 info->vision.detectEyes( info->vision.camFrame );
						 }
						 else
						 {
							 info->vision.save_eyeRegion( info->vision.camFrame, info->vision.eyeRegionX, info->vision.eyeRegionY, info->vision.eyeRegionWidth, info->vision.eyeRegionHeight );
						
							 try
							 {
								 /*-------------RGBtoHSV--------------*/
								 //info->vision.convertEyeRegionRGBtoHSV( info->vision.eyefram );
								 info->vision.settGrayEyeRegion( info->vision.eyefram ); //轉灰階並找出眼睛正中心點

								 if( info->isStrategyRun )
								 {	
									 info->strategy.adult.run();
									 this->sendSerialData();
								 }

								 /*----------Hough Circle-------------*/
								 //info->vision.HoughCircle( info->vision.eyefram );

								 /*-----------Find object-------------*/
								 //info->vision.run( GAZECONTROL_EVENT::GAZECONTROl );//用顏色找眼球區域

								 /*------------------Display the eye fram--------------------*/
								 this->display( info->vision.eyefram );
								 info->strategy.adult.gaze.isReallyfindEye = true;
							 }
							 catch (...)
							 {
								info->vision.isfindEye = false;
								info->vision.isInitialHSVfram = false;
								info->vision.isInitialGrayfram = false;
								info->strategy.adult.gaze.isReallyfindEye = false;
								printf("\nNofound\n");
							 }
							 
							 
						 }
						 
					 }
					
					 /*------------------Display --------------------*/
					 this->displayInfo();
					 // Calculate FPS
					 frameWatch->Stop();
					 this->framePerSecond = (int)(frameWatch->ElapsedMilliseconds == 0 ? 0 : 1000/frameWatch->ElapsedMilliseconds); 
					 this->toolStripStatusLabelFPS->Text = System::Convert::ToString( this->framePerSecond );
					 frameWatch->Restart();

				 } //--- End of try ---//


				 catch (System::Exception^ e)
				 {
					 System::Windows::Forms::MessageBox::Show( e->ToString() );
				 } //--- End of catch ---//


			 } //--- End of While ---//	
		 }


		 public: System::Void display ( IplImage *camFrameToDisplay ){

					 //this->updateUI( info->vision.objectIndex );

					 cv::Mat matCamFrame( camFrameToDisplay ,0 );	//0表示不複製內容，也就是兩個變數的 row data 共用同個記憶體位置，header 則各自有

					 info->strategy.adult.gaze.EyemainX = info->vision.eyefram->width/2;
					 info->strategy.adult.gaze.EyemainY = info->vision.eyefram->height/2;

					 //cvRectangle(camFrameToDisplay ,cvPoint(25,25) ,cvPoint(20,20) ,CV_RGB(255,0,0) ,1);
					 
					 /*------畫中心點和移動點並連線---------*/
					 //cv::circle(matCamFrame , cvPoint( info->strategy.adult.gaze.EyemainX,info->strategy.adult.gaze.EyemainY ),1 ,CV_RGB(0,0,255) ,2);
					 cv::circle(matCamFrame , cvPoint( info->strategy.adult.gaze.IniEyeX,info->strategy.adult.gaze.IniEyeY ),1 ,CV_RGB(0,0,255) ,2);
					 if ( info->strategy.adult.gaze.isInitialEyePoint )
					 {
						 cv::circle(matCamFrame , cvPoint(info->vision.eyemaintX,info->vision.eyemaintY ),1 ,CV_RGB(255,0,0) ,2);
						 cvLine(camFrameToDisplay,cvPoint(info->vision.eyemaintX,info->vision.eyemaintY ),cvPoint( info->strategy.adult.gaze.IniEyeX,info->strategy.adult.gaze.IniEyeY ),CV_RGB(255,255,0),2);
						 //cvLine(camFrameToDisplay,cvPoint(info->vision.eyemaintX,info->vision.eyemaintY ),cvPoint( info->strategy.adult.gaze.EyemainX,info->strategy.adult.gaze.EyemainY ),CV_RGB(255,255,0),2);
						 
						 //------計算中心點與移動後的向量------//
						 calPointsVector( info->strategy.adult.gaze.IniEyeX, info->strategy.adult.gaze.IniEyeY, info->vision.eyemaintX,info->vision.eyemaintY );
					 }
					 
					 
					 
					 this->pictureBoxGaze->Image = gcnew System::Drawing::Bitmap(
						 camFrameToDisplay->width,
						 camFrameToDisplay->height,
						 camFrameToDisplay->width*3,
						 System::Drawing::Imaging::PixelFormat::Format24bppRgb,
						 System::IntPtr(camFrameToDisplay->imageData)
						 );

				 } //end of the event

			public: System::Void calPointsVector( int px1,int py1,int px2,int py2){

						info->vision.eyeMoveVectorX = ( px2 - px1 );
						info->vision.eyeMoveVectorY = ( py2 - py1 );
						double L = (info->vision.eyeMoveVectorX*info->vision.eyeMoveVectorX)+(info->vision.eyeMoveVectorY*info->vision.eyeMoveVectorY);
						info->vision.eyeMoveVectorLength = sqrt(L);
						
						printf("\nVector X = %d,Vector Y = %d\n",info->vision.eyeMoveVectorX,info->vision.eyeMoveVectorY );
						printf("\nVector L = %f\n",info->vision.eyeMoveVectorLength );
					}

// 			public: System::Void display ( IplImage *camFrameToDisplay ){
// 
// 						//this->updateUI( info->vision.objectIndex );
// 						
// 						cv::Mat matCamFrame( camFrameToDisplay ,0 );	//0表示不複製內容，也就是兩個變數的 row data 共用同個記憶體位置，header 則各自有
// 						
// 						//mark selected
// 						unsigned char h,s,v;
// 						for ( int j=0 ; j<camFrameToDisplay->height ; j++)
// 						{
// 							for ( int i=0 ; i<camFrameToDisplay->width ; i++)
// 							{
// 								h = info->vision.camFrame_HSV->imageData[(j*camFrameToDisplay->width+i)*3];
// 								s = info->vision.camFrame_HSV->imageData[(j*camFrameToDisplay->width+i)*3+1];
// 								v = info->vision.camFrame_HSV->imageData[(j*camFrameToDisplay->width+i)*3+2];
// 								if (info->vision.hsvObjLUT.color1[h]&info->vision.hsvObjLUT.color2[s]&info->vision.hsvObjLUT.color3[v]&(0x01<<info->vision.objectIndex))
// 								{
// 									camFrameToDisplay->imageData[(j*camFrameToDisplay->width+i)*3] = (unsigned char)230;	//B
// 									camFrameToDisplay->imageData[(j*camFrameToDisplay->width+i)*3+1] = (unsigned char)140;	//G
// 									camFrameToDisplay->imageData[(j*camFrameToDisplay->width+i)*3+2] = (unsigned char)20;	//R
// 								}
// 							}
// 						}
// 
// 						//draw object rectangle
// 						for (int i=0 ;i<4 ;i++)
// 						{
// 							for (std::vector<ObjectRegion>::iterator obj=info->objectRegion[i].begin() ;obj!=info->objectRegion[i].end() ;++obj)
// 							{
// 								//用不同顏色框出不同物件
// 								if ( i==0 && (info->vision.objectIndex == OBJECT::COLOR1) )
// 								{
// 									cvRectangle(camFrameToDisplay ,cvPoint((*obj).leftBoundary , (*obj).topBoundary) ,cvPoint((*obj).rightBoundary , (*obj).bottomBoundary) ,CV_RGB(255,0,0) ,1);
// 									cv::circle(matCamFrame ,obj->mainPoint ,1 ,CV_RGB(255,0,0) ,2);
// 									// Display mainPoint
// 									this->toolStripStatusLabelMainPointX->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.x );
// 									this->toolStripStatusLabelMainPointY->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.y );
// 								} 
// 								else if( i==1 && (info->vision.objectIndex == OBJECT::COLOR2) )
// 								{
// 									cvRectangle(camFrameToDisplay ,cvPoint((*obj).leftBoundary , (*obj).topBoundary) ,cvPoint((*obj).rightBoundary , (*obj).bottomBoundary) ,CV_RGB(0,255,0) ,1);
// 									cv::circle(matCamFrame ,obj->mainPoint ,1 ,CV_RGB(0,255,0) ,2);
// 									// Display mainPoint
// 									this->toolStripStatusLabelMainPointX->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.x );
// 									this->toolStripStatusLabelMainPointY->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.y );
// 								}
// 								else if( i==2 && (info->vision.objectIndex == OBJECT::COLOR3) )
// 								{
// 									cvRectangle(camFrameToDisplay ,cvPoint((*obj).leftBoundary , (*obj).topBoundary) ,cvPoint((*obj).rightBoundary , (*obj).bottomBoundary) ,CV_RGB(0,0,255) ,1);
// 									cv::circle(matCamFrame ,obj->mainPoint ,1 ,CV_RGB(0,0,255) ,2);
// 									// Display mainPoint
// 									this->toolStripStatusLabelMainPointX->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.x );
// 									this->toolStripStatusLabelMainPointY->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.y );
// 								}
// 								else if( i==3 && (info->vision.objectIndex == OBJECT::COLOR4) )
// 								{
// 									cvRectangle(camFrameToDisplay ,cvPoint((*obj).leftBoundary , (*obj).topBoundary) ,cvPoint((*obj).rightBoundary , (*obj).bottomBoundary) ,CV_RGB(0,100,200) ,1);
// 									cv::circle(matCamFrame ,obj->mainPoint ,1 ,CV_RGB(255,0,0) ,2);
// 									// Display mainPoint
// 									this->toolStripStatusLabelMainPointX->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.x );
// 									this->toolStripStatusLabelMainPointY->Text = System::Convert::ToString( info->objectRegion[info->vision.objectIndex][0].mainPoint.y );
// 								}
// 
// 							}
// 						}
// 
// 						try
// 						{
// 							std::vector<ObjectRegion> showObj;
// 
// 							if ( !info->objectRegion[info->vision.objectIndex].empty() )
// 							{
// 								showObj.push_back( info->objectRegion[info->vision.objectIndex][0] );
// 								this->labelObj_pixcels->Text = System::Convert::ToString( showObj[0].pixelNumbers );
// 							}
// 						}
// 						catch (...)
// 						{
// 							printf("\n\n\n\n\n");
// 						}
// 
// 						//draw object
// 						this->pictureBoxGaze->Image = gcnew System::Drawing::Bitmap(
// 							camFrameToDisplay->width,
// 							camFrameToDisplay->height,
// 							camFrameToDisplay->width*3,
// 							System::Drawing::Imaging::PixelFormat::Format24bppRgb,
// 							System::IntPtr(camFrameToDisplay->imageData)
// 							);
// 
// 
// 
// 
// 					} //end of the event

private: System::Void radioButtonObj_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

			 // Object Check Mark

			 if ( this->radioButtonObject1->Checked )
				 info->vision.objectIndex = OBJECT::COLOR1;
			 else if ( this->radioButtonObject2->Checked )
				 info->vision.objectIndex = OBJECT::COLOR2;
			 else if ( this->radioButtonObject3->Checked )
				 info->vision.objectIndex = OBJECT::COLOR3;
			 else if ( this->radioButtonObject4->Checked )
				 info->vision.objectIndex = OBJECT::COLOR4;
			 
			 //update UI
			 this->updateObjColorLUT(info->vision.objectIndex);
			 this->updateUI(info->vision.objectIndex);

		 }
private: System::Void buttonSetCam_Click(System::Object^  sender, System::EventArgs^  e) {

			 info->vision.VI->showSettingsWindow(info->vision.camID);

		 }
private: System::Void pictureBoxColorWheel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 
			 //決定要移動的點
			 static double dH1S1, dH1S2, dH2S1, dH2S2 = 0;

			 dH1S1 = tool.calcDis( e->X, e->Y, H1S1.X, H1S1.Y );
			 dH1S2 = tool.calcDis( e->X, e->Y, H1S2.X, H1S2.Y );
			 dH2S1 = tool.calcDis( e->X, e->Y, H2S1.X, H2S1.Y );
			 dH2S2 = tool.calcDis( e->X, e->Y, H2S2.X, H2S2.Y );

			 double min = tool.getMin(  tool.getMin( dH1S1,dH1S2,dH2S1) , dH2S2 );

			 if ( min == dH1S1 ) this->dotMoveNumber = COLORWHEEL_DOT::H1S1;
			 else if ( min == dH1S2 ) this->dotMoveNumber = COLORWHEEL_DOT::H1S2;
			 else if ( min == dH2S1 ) this->dotMoveNumber = COLORWHEEL_DOT::H2S1;
			 else if ( min == dH2S2 ) this->dotMoveNumber = COLORWHEEL_DOT::H2S2;

			 this->dotMove = true;
		 }
private: System::Void pictureBoxColorWheel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

			 static int radius, ang = 0;
			 radius = (int) tool.limitValue( tool.calcDis( e->X,e->Y,90,90 ), 0, 90 );
			 ang = (int) tool.calcPolarAngle( e->X,e->Y,90,90 );

			 this->labelColorHMove->Text = System::Convert::ToString( tool.pointDecimal((double)ang/359*255,0) );
			 this->labelColorSMove->Text = System::Convert::ToString( tool.pointDecimal((double)radius/90*255,0) );

			 /*---------------------------------------------------------------*/
			 if ( this->dotMove )
			 {

				 switch ( this->dotMoveNumber )
				 {				 
				 case COLORWHEEL_DOT::H1S1 :
					 this->startHAng = ang;
					 this->startSRadius = radius;
					 break;

				 case COLORWHEEL_DOT::H1S2 :
					 this->startHAng = ang;
					 this->endSRadius = radius;
					 break;

				 case COLORWHEEL_DOT::H2S1 :
					 this->endHAng = ang;
					 this->startSRadius = radius;
					 break;

				 case COLORWHEEL_DOT::H2S2 :
					 this->endHAng = ang;
					 this->endSRadius = radius;
					 break;
				 } 

				 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = (int) ( (double)startHAng/359*255 );
				 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = (int) ( (double)endHAng/359*255 );
				 info->vision.hsvObjRange[info->vision.objectIndex].color2.min = (int) ( (double)startSRadius/90*255 );
				 info->vision.hsvObjRange[info->vision.objectIndex].color2.max = (int) ( (double)endSRadius/90*255 );

				 this->updateObjColorLUT(info->vision.objectIndex);
				 this->updateUI(info->vision.objectIndex);
			 }

		 }
private: System::Void pictureBoxColorWheel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->dotMove = false;
		 }
	public: System::Void updateObjColorLUT ( unsigned char objIndex )
			{
				for (int i=0 ; i < 256 ; i++)
				{
					info->vision.hsvObjLUT.color1[i] &= ~(0x01<<objIndex);//先歸零
					info->vision.hsvObjLUT.color2[i] &= ~(0x01<<objIndex);
					info->vision.hsvObjLUT.color3[i] &= ~(0x01<<objIndex);

					//H
					if ( info->vision.hsvObjRange[objIndex].color1.min >	info->vision.hsvObjRange[objIndex].color1.max )
					{//繞過原點
						if ( i>=info->vision.hsvObjRange[objIndex].color1.min || i<=info->vision.hsvObjRange[objIndex].color1.max )
						{
							info->vision.hsvObjLUT.color1[i] |= 0x01<<objIndex;
						}
					}else{//正常範圍
						if ( i>=info->vision.hsvObjRange[objIndex].color1.min && i<=info->vision.hsvObjRange[objIndex].color1.max )
						{
							info->vision.hsvObjLUT.color1[i] |= 0x01<<objIndex;
						}
					}

					//S
					if ( i>=info->vision.hsvObjRange[objIndex].color2.min && i<=info->vision.hsvObjRange[objIndex].color2.max )
					{
						info->vision.hsvObjLUT.color2[i] |= 0x01<<objIndex;
					}

					//V
					if ( i>=info->vision.hsvObjRange[objIndex].color3.min && i<=info->vision.hsvObjRange[objIndex].color3.max )
					{
						info->vision.hsvObjLUT.color3[i] |= 0x01<<objIndex;
					}
				}
			}
	public: System::Void updateUI ( unsigned char objIndex ){

				//更新 colorWheel 顯示值
				this->labelColorHMin->Text = System::Convert::ToString( info->vision.hsvObjRange[objIndex].color1.min );
				this->labelColorSMin->Text = System::Convert::ToString( info->vision.hsvObjRange[objIndex].color2.min );
				this->labelColorVMin->Text = System::Convert::ToString( info->vision.hsvObjRange[objIndex].color3.min );
				this->labelColorHMax->Text = System::Convert::ToString( info->vision.hsvObjRange[objIndex].color1.max );
				this->labelColorSMax->Text = System::Convert::ToString( info->vision.hsvObjRange[objIndex].color2.max );
				this->labelColorVMax->Text = System::Convert::ToString( info->vision.hsvObjRange[objIndex].color3.max );


				//計算 COLOR WHEEL 介面值
				startHAng = (double) info->vision.hsvObjRange[objIndex].color1.min/255*360;
				endHAng = (double) info->vision.hsvObjRange[objIndex].color1.max/255*360;

				startSRadius = (double) info->vision.hsvObjRange[objIndex].color2.min/255*90;
				endSRadius = (double) info->vision.hsvObjRange[objIndex].color2.max/255*90;

				H1S1.X = tool.calcCartesianX(startSRadius,tool.setAngleInRange(270+startHAng),90,90);
				H1S2.X = tool.calcCartesianX(endSRadius,tool.setAngleInRange(270+startHAng),90,90);
				H2S1.X = tool.calcCartesianX(startSRadius,tool.setAngleInRange(270+endHAng),90,90);
				H2S2.X = tool.calcCartesianX(endSRadius,tool.setAngleInRange(270+endHAng),90,90);

				H1S1.Y = tool.calcCartesianY(startSRadius,tool.setAngleInRange(270+startHAng),90,90);
				H1S2.Y = tool.calcCartesianY(endSRadius,tool.setAngleInRange(270+startHAng),90,90);
				H2S1.Y = tool.calcCartesianY(startSRadius,tool.setAngleInRange(270+endHAng),90,90);
				H2S2.Y = tool.calcCartesianY(endSRadius,tool.setAngleInRange(270+endHAng),90,90);

				//更新 COLOR WHEEL
				delete colorWheelBmpUsing; //釋放記憶體
				colorWheelBmpUsing = gcnew Bitmap( colorWheelBmpFileRead );
				pictureBoxColorWheel->Image = colorWheelBmpUsing;

				colorWheelGraphics =  Graphics::FromImage(colorWheelBmpUsing);
				this->colorWheelEdge = gcnew Pen ( Color::Black,1);
				this->colorWheelDot = gcnew Pen ( Color::Red, 2);

				int angleStart = tool.setAngleInRange(270+startHAng);
				int angleRange = tool.setAngleInRange(endHAng-startHAng);

				//ARC
				if ( startSRadius != 0)
				{

					this->colorWheelGraphics->DrawArc( this->colorWheelEdge, 90-startSRadius,90-startSRadius,
						startSRadius*2,startSRadius*2,
						angleStart,angleRange );
				}

				if ( endSRadius != 0 )
				{
					this->colorWheelGraphics->DrawArc( this->colorWheelEdge, 90-endSRadius,90-endSRadius,
						endSRadius*2,endSRadius*2,
						angleStart,angleRange );
				}

				//line
				this->colorWheelGraphics->DrawLine( this->colorWheelEdge, H1S1, H1S2 );
				this->colorWheelGraphics->DrawLine( this->colorWheelEdge, H2S1, H2S2 );

				//Dot
				this->colorWheelGraphics->DrawEllipse( this->colorWheelDot, (int) H1S1.X, (int) H1S1.Y, 2, 2 );
				this->colorWheelGraphics->DrawEllipse( this->colorWheelDot, (int) H1S2.X, (int) H1S2.Y, 2, 2 );
				this->colorWheelGraphics->DrawEllipse( this->colorWheelDot, (int) H2S1.X, (int) H2S1.Y, 2, 2 );
				this->colorWheelGraphics->DrawEllipse( this->colorWheelDot, (int) H2S2.X, (int) H2S2.Y, 2, 2 );

				pictureBoxColorWheel->Refresh();

				/*--------------------------------------------------*/

				//更新 GRAY LEVEL 介面值
				vUP = 180 - (double) info->vision.hsvObjRange[objIndex].color3.min/255*180;
				vDown = 180 - (double) info->vision.hsvObjRange[objIndex].color3.max/255*180;

				//更新 COLOR WHEEL 介面

				delete grayLevelBmpUsing; //釋放記憶體
				grayLevelBmpUsing = gcnew Bitmap( grayLevelBmpFileRead );
				pictureBoxGrayLevel->Image = grayLevelBmpUsing;

				grayLevelGraphics =  Graphics::FromImage(grayLevelBmpUsing);
				this->grayLevelEdge = gcnew Pen ( Color::Red,2);

				this->grayLevelGraphics->DrawLine( this->grayLevelEdge, 0, vUP, 25, vUP );
				this->grayLevelGraphics->DrawLine( this->grayLevelEdge, 0, vDown, 25, vDown );

				pictureBoxGrayLevel->Refresh();

				/*--------------------------------------------------------------------*/

				switch (objIndex)
				{
				case OBJECT::COLOR1:	this->radioButtonObject1->Checked = true;	break;
				case OBJECT::COLOR2:	this->radioButtonObject2->Checked = true;	break;
				case OBJECT::COLOR3:	this->radioButtonObject3->Checked = true;	break;
				case OBJECT::COLOR4:	this->radioButtonObject4->Checked = true;	break;
				default:break;
				}



			} // end of the event
private: System::Void pictureBoxCamOneInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

			 if ( info->isCameraOpen)
			 {
				 //右鍵：增加範圍
				 if ( e->Button == System::Windows::Forms::MouseButtons::Right )
				 {
					 //儲存點下的HSV
					 ObjectColorRange tempRange;

					 tempRange.color1.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3];
					 tempRange.color2.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+1];
					 tempRange.color3.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+2];

					 // H 更新範圍
					 if ( tempRange.color1.point-10 < 0 )
						 tempRange.color1.min = tempRange.color1.point - 10 + 256;
					 else
						 tempRange.color1.min = tempRange.color1.point - 10;

					 if ( tempRange.color1.point+10 > 255 )
						 tempRange.color1.max = tempRange.color1.point + 10 - 256;
					 else
						 tempRange.color1.max = tempRange.color1.point + 10;

					 // S 更新範圍
					 if( tempRange.color2.point-50 < 0 )
						 tempRange.color2.min = 0;
					 else
						 tempRange.color2.min = tempRange.color2.point - 50;

					 if( tempRange.color2.point+50 > 255 )
						 tempRange.color2.max = 255;
					 else
						 tempRange.color2.max = tempRange.color2.point + 50;

					 // V 更新範圍
					 if( tempRange.color3.point-50 < 0 )
						 tempRange.color3.min = 0;
					 else
						 tempRange.color3.min = tempRange.color3.point - 50;

					 if( tempRange.color3.point+50 > 255 )
						 tempRange.color3.max = 255;
					 else
						 tempRange.color3.max = tempRange.color3.point + 50;

					 //增加範圍				 
					 unsigned char minH = info->vision.hsvObjRange[info->vision.objectIndex].color1.min;
					 unsigned char maxH = info->vision.hsvObjRange[info->vision.objectIndex].color1.max;

					 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = tool.getMin(minH ,tempRange.color1.min); //System::Math::Min(minH ,tempRange.color1.min);
					 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = tool.getMax(maxH ,tempRange.color1.max); //System::Math::Max(maxH ,tempRange.color1.max);

					 // H 更新範圍
					 if ( minH > maxH || tempRange.color1.min > tempRange.color1.max )
					 {
						 if ( info->vision.hsvObjRange[info->vision.objectIndex].color1.max >= info->vision.hsvObjRange[info->vision.objectIndex].color1.min )
						 {
							 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = 0;
							 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = 255;
						 }
					 }

					 // S 更新範圍
					 if ( tempRange.color2.min < info->vision.hsvObjRange[info->vision.objectIndex].color2.min ) //比小時，右鍵小於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.min = tempRange.color2.min;
					 if ( tempRange.color2.max > info->vision.hsvObjRange[info->vision.objectIndex].color2.max ) //比大時，右鍵大於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.max = tempRange.color2.max;

					 // V 更新範圍
					 if ( tempRange.color3.min < info->vision.hsvObjRange[info->vision.objectIndex].color3.min ) //比小時，右鍵小於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.min = tempRange.color3.min;
					 if ( tempRange.color3.max > info->vision.hsvObjRange[info->vision.objectIndex].color3.max ) //比大時，右鍵大於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.max = tempRange.color3.max;
				 }

				 //左鍵：選取範圍
				 else if ( e->Button == System::Windows::Forms::MouseButtons::Left )
				 {
					 //儲存點下的HSV
					 info->vision.hsvObjRange[info->vision.objectIndex].color1.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3];
					 info->vision.hsvObjRange[info->vision.objectIndex].color2.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+1];
					 info->vision.hsvObjRange[info->vision.objectIndex].color3.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+2];


					 // H 更新範圍
					 if ( info->vision.hsvObjRange[info->vision.objectIndex].color1.point-10 < 0 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = info->vision.hsvObjRange[info->vision.objectIndex].color1.point - 10 + 256;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = info->vision.hsvObjRange[info->vision.objectIndex].color1.point - 10;

					 if ( info->vision.hsvObjRange[info->vision.objectIndex].color1.point+10 > 255 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = info->vision.hsvObjRange[info->vision.objectIndex].color1.point + 10 - 256;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = info->vision.hsvObjRange[info->vision.objectIndex].color1.point + 10;

					 // S 更新範圍
					 if( info->vision.hsvObjRange[info->vision.objectIndex].color2.point-50 < 0 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.min = 0;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.min = info->vision.hsvObjRange[info->vision.objectIndex].color2.point - 50;

					 if( info->vision.hsvObjRange[info->vision.objectIndex].color2.point+50 > 255 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.max = 255;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.max = info->vision.hsvObjRange[info->vision.objectIndex].color2.point + 50;

					 // V 更新範圍
					 if( info->vision.hsvObjRange[info->vision.objectIndex].color3.point-50 < 0 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.min = 0;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.min = info->vision.hsvObjRange[info->vision.objectIndex].color3.point - 50;

					 if( info->vision.hsvObjRange[info->vision.objectIndex].color3.point+50 > 255 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.max = 255;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.max = info->vision.hsvObjRange[info->vision.objectIndex].color3.point + 50;
				 }


				 //更新LUT
				 this->updateObjColorLUT( info->vision.objectIndex );

				 //更新人機介面
				 this->updateUI( info->vision.objectIndex );

			 }	// end of isCamOpen or isRunSimulation
		 }
private: System::Void pictureBoxCamOneInput_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

// 			 if ( info->isCameraOpen )
// 			 {
// 				 this->toolStripStatusLabelMousePointH->Text = System::Convert::ToString(info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3]);
// 				 this->toolStripStatusLabelMousePointS->Text = System::Convert::ToString(info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+1]);
// 				 this->toolStripStatusLabelMousePointV->Text = System::Convert::ToString(info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+2]);
// 			 }

		 }
private: System::Void buttonSaveColor_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::IO::FileStream^ fs;
			 System::IO::StreamWriter^ sw;

			 fs = gcnew System::IO::FileStream( ".\\Parameters\\Object_Color.txt" , System::IO::FileMode::Create );
			 sw = gcnew System::IO::StreamWriter( fs );

			 for ( int i=0 ;i<9 ;i++ )
			 {
				 sw->WriteLine( "-- ColorIndex "+i+" --" );

				 sw->WriteLine( 
					 info->vision.hsvObjRange[i].color1.point+" "+
					 info->vision.hsvObjRange[i].color1.max+" "+
					 info->vision.hsvObjRange[i].color1.min
					 );

				 sw->WriteLine( 
					 info->vision.hsvObjRange[i].color2.point+" "+
					 info->vision.hsvObjRange[i].color2.max+" "+
					 info->vision.hsvObjRange[i].color2.min
					 );

				 sw->WriteLine( 
					 info->vision.hsvObjRange[i].color3.point+" "+
					 info->vision.hsvObjRange[i].color3.max+" "+
					 info->vision.hsvObjRange[i].color3.min
					 );

				 sw->WriteLine("");
			 }

			 sw->Close();
			 fs->Close();
		 }
private: System::Void buttonLoadColor_Click(System::Object^  sender, System::EventArgs^  e) {

			 System::IO::FileStream ^fs;
			 System::IO::StreamReader ^sr;

			 array<String^> ^split;
			 array<wchar_t> ^delimiter={' '};//以空格做分割
			 int tempColorIndex;

			 fs = gcnew System::IO::FileStream( ".\\Parameters\\Object_Color.txt" , System::IO::FileMode::Open ,System::IO::FileAccess::Read );
			 sr = gcnew System::IO::StreamReader( fs );
			 String ^line;

			 while( (line=sr->ReadLine()) != nullptr )
			 {
				 split = line->Split(delimiter);
				 tempColorIndex = Convert::ToInt32( split[2] );
				 line = sr->ReadLine();
				 split = line->Split(delimiter);
				 info->vision.hsvObjRange[tempColorIndex].color1.point = Convert::ToInt32(split[0]);
				 info->vision.hsvObjRange[tempColorIndex].color1.max = Convert::ToInt32(split[1]);
				 info->vision.hsvObjRange[tempColorIndex].color1.min = Convert::ToInt32(split[2]);
				 line = sr->ReadLine();
				 split = line->Split(delimiter);
				 info->vision.hsvObjRange[tempColorIndex].color2.point = Convert::ToInt32(split[0]);
				 info->vision.hsvObjRange[tempColorIndex].color2.max = Convert::ToInt32(split[1]);
				 info->vision.hsvObjRange[tempColorIndex].color2.min = Convert::ToInt32(split[2]);
				 line = sr->ReadLine();
				 split = line->Split(delimiter);
				 info->vision.hsvObjRange[tempColorIndex].color3.point = Convert::ToInt32(split[0]);
				 info->vision.hsvObjRange[tempColorIndex].color3.max = Convert::ToInt32(split[1]);
				 info->vision.hsvObjRange[tempColorIndex].color3.min = Convert::ToInt32(split[2]);
				 sr->ReadLine();

				 this->updateObjColorLUT(tempColorIndex);
			 }

			 //更新人機介面
			 this->updateUI(info->vision.objectIndex);
		 }
private: System::Void buttonRunStrategy_Click(System::Object^  sender, System::EventArgs^  e) {

			 if ( !info->isStrategyRun )
			 {
				 info->isStrategyRun = true;
				 info->strategy.adult.runInitial();
				 this->buttonRunStrategy->Text = "STOP";
			 }

			 else if ( info->isStrategyRun )
			 {
				 info->isStrategyRun = false;
				 this->buttonRunStrategy->Text = "Run Strategy";
				 //將STATE 變為INITIAL 也就是 = 0
				 info->strategy.strategyState = 0;

				 //送出 stop; dis = 0; angle = 0;
				 info->serialPort.tx.data.bodyMotionCode = MOTION::BODY::STOP;

				 //dis = 0
				 info->serialPort.tx.arr[2] = 0;		//(int) (tempDis*100+32768)%256;	
				 info->serialPort.tx.arr[3] = 128;	//(int) (tempDis*100+32768)/256;

				 //angle = 0
				 info->serialPort.tx.arr[4] = 0;		//(int) (tempDis*100+32768)%256;	
				 info->serialPort.tx.arr[5] = 128;	//(int) (tempDis*100+32768)/256;
				 this->sendSerialData();
				 //this->watchEventParaForm->sendSerialData();
			 }
		 }

public: System::Void sendSerialData(){

			//Counter 只會宣告一次而已，因為加上 static 描述子
			static int count = 0;

			//開始設定要送出的資料

			//設定檔頭
			info->serialPort.tx.data.startCode = 255;

			// 				//若無body motion，直接送出STOP命令 (已經寫在 setNextBodyMotion)
			// 				if ( info->strategy.adult.globalpara.disableBodyMotion )
			// 					info->serialPort.tx.data.bodyMotionCode = MOTION::BODY::STOP;

			//最後計算 checkSum
			this->setCheckSum( info->serialPort.tx.arr ,SERIALPORT_TX_LEN );

			//並將要送出的資料，呈現在介面裡面
			//this->displayInfo();
			this->displayTxInfo();

			//Serial Port 沒打開，就直接return
			if( !info->isSerialPortOpen )
				return;

			//將要送出的資料，整理成一個 DATA ARRAY
			array<unsigned char>^ data = gcnew array<unsigned char>(SERIALPORT_TX_LEN);
			for ( int i=0 ;i<data->Length ;i++ )
				data[i] = info->serialPort.tx.arr[i];

			//送出資訊，若無delay count，直接送出，否則要等一下
			if ( info->strategy.adult.globalpara.sendDelayCount != 0  )
			{
				//若count整除sendDelayCount則送出資訊，否則跳到count++
				if ( count%info->strategy.adult.globalpara.sendDelayCount == 0 ){
					this->serialPortRS232->Write( data ,0 ,data->Length );
					printf("delay count &5d\n", count);
				}
			}
			else
				this->serialPortRS232->Write( data ,0 ,data->Length );

			//delay count ++ 
			count++;


		}
private: System::Void setCheckSum( unsigned char* arr ,int len )
			{
				arr[len-1] = 0;
				for ( int i=1 ;i<len-1 ;i++ )
				{
					arr[len-1] +=arr[i];
				}
				arr[len-1] = ~(arr[len-1]);
			}
	public: System::Void displayInfo(){

				this->displayRxInfo();
				this->displayTxInfo();
			}
	public: System::Void displayRxInfo(){

				this->labelRxDip->Text = System::Convert::ToString( info->serialPort.rx.data.dip );
				this->labelRxTiltPos->Text = System::Convert::ToString( info->serialPort.rx.data.tiltPos );
				this->labelRxPanPos->Text = System::Convert::ToString( info->serialPort.rx.data.panPos );
				this->labelRxBodyDoing->Text = System::Convert::ToString( info->serialPort.rx.data.bodyDoingCode );
				this->labelSensorMagAzimuth->Text = System::Convert::ToString( info->sensor.azimuthDegree );

				//轉換角度
				this->labelRxTiltPosAng->Text = System::Convert::ToString( tool.pointDecimal(info->strategy.getHeadTiltAngle(),0) );
				this->labelRxPanPosAng->Text = System::Convert::ToString( tool.pointDecimal(info->strategy.getHeadPanAngle(),0)  );

				//State Info
				this->labelRelativeAzimuth->Text = System::Convert::ToString( tool.pointDecimal(info->sensor.getRelativeAzimuth(),2) );

				this->labelIsBodyMotionDone->Text = System::Convert::ToString(info->strategy.isBodyMotionDone);
				this->labelRobotStableWait->Text = System::Convert::ToString( info->strategy.waitRobotStableWait );

				switch( info->strategy.headState )
				{
					case MOTION::HEAD::STATE::SEARCH_STRAIGHT :			this->labelRobotHeadSearchState->Text = "Straight_1st";	break;
					case MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE :	this->labelRobotHeadSearchState->Text = "Straight_2nd";	break;
					case MOTION::HEAD::STATE::SEARCH_STRAIGHT_THIRD :	this->labelRobotHeadSearchState->Text = "Straight_3rd";	break;
					case MOTION::HEAD::STATE::SEARCH_STRAIGHT_FORTH :	this->labelRobotHeadSearchState->Text = "Straight_4th";	break;
					case MOTION::HEAD::STATE::SEARCH_STRAIGHT_FIFTH :	this->labelRobotHeadSearchState->Text = "Straight_5th";	break;
					case MOTION::HEAD::STATE::SEARCH_LEFT:				this->labelRobotHeadSearchState->Text = "Left_1st";		break;
					case MOTION::HEAD::STATE::SEARCH_LEFT_TWICE:		this->labelRobotHeadSearchState->Text = "Left_2nd";		break;
					case MOTION::HEAD::STATE::SEARCH_LEFT_THIRD:		this->labelRobotHeadSearchState->Text = "Left_3rd";		break;
					case MOTION::HEAD::STATE::SEARCH_LEFT_FOURTH:		this->labelRobotHeadSearchState->Text = "Left_4th";		break;
					case MOTION::HEAD::STATE::SEARCH_RIGHT:				this->labelRobotHeadSearchState->Text = "Right_1st";	break;
					case MOTION::HEAD::STATE::SEARCH_RIGHT_TWICE:		this->labelRobotHeadSearchState->Text = "Right_2nd";	break;
					case MOTION::HEAD::STATE::SEARCH_RIGHT_THIRD:		this->labelRobotHeadSearchState->Text = "Right_3rd";	break;
					case MOTION::HEAD::STATE::SEARCH_RIGHT_FOURTH:		this->labelRobotHeadSearchState->Text = "Right_4th";	break;
					default:											this->labelRobotHeadSearchState->Text = "x";			break;
				}

				// dip binary
				int decDip = 0;

				if ( info->serialPort.rx.data.dip >= 100 )
					decDip = info->serialPort.rx.data.dip - 100;
				else
					decDip = info->serialPort.rx.data.dip;

				int dipBinary[6];
				dipBinary[5] = (int) (decDip/32); decDip = decDip - 32*dipBinary[5];
				dipBinary[4] = (int) (decDip/16); decDip = decDip - 16*dipBinary[4];
				dipBinary[3] = (int) (decDip/8);  decDip = decDip - 8*dipBinary[3];
				dipBinary[2] = (int) (decDip/4);  decDip = decDip - 4*dipBinary[2];
				dipBinary[1] = (int) (decDip/2);  decDip = decDip - 2*dipBinary[1];
				dipBinary[0] = (int) (decDip/1);  decDip = decDip - 1*dipBinary[0];

				this->labelRxDipBinary5->Text = System::Convert::ToString( dipBinary[5] );
				this->labelRxDipBinary4->Text = System::Convert::ToString( dipBinary[4] );
				this->labelRxDipBinary3->Text = System::Convert::ToString( dipBinary[3] );
				this->labelRxDipBinary2->Text = System::Convert::ToString( dipBinary[2] );
				this->labelRxDipBinary1->Text = System::Convert::ToString( dipBinary[1] );
				this->labelRxDipBinary0->Text = System::Convert::ToString( dipBinary[0] );

			}
	public: System::Void displayTxInfo()
			{
				unsigned char displayCode;
				//不做身體動作，debug，實際不送出，只拿來顯示用
				if ( info->strategy.disableBodyMotion )
					displayCode = info->strategy.disableBodyMotionCode;
				else
					displayCode = info->serialPort.tx.data.bodyMotionCode;

				//Body Motion Code
				switch ( displayCode )
				{
				case MOTION::BODY::DONE:		this->labelTxBodyMotion->Text = "NONE";			break;					

					//單步
				case MOTION::BODY::STEP_F:		this->labelTxBodyMotion->Text = "STEP_F";		break;
				case MOTION::BODY::STEP_FF:		this->labelTxBodyMotion->Text = "STEP_FF";		break;
				case MOTION::BODY::STEP_FFF:	this->labelTxBodyMotion->Text = "STEP_FFF";		break;
				case MOTION::BODY::STEP_B:		this->labelTxBodyMotion->Text = "STEP_B";		break;
				case MOTION::BODY::STEP_BB:		this->labelTxBodyMotion->Text = "STEP_BB";		break;
				case MOTION::BODY::SHIFT_L:		this->labelTxBodyMotion->Text = "SHIFT_L";		break;
				case MOTION::BODY::SHIFT_LL:	this->labelTxBodyMotion->Text = "SHIFT_LL";		break;
				case MOTION::BODY::SHIFT_R:		this->labelTxBodyMotion->Text = "SHIFT_R";		break;
				case MOTION::BODY::SHIFT_RR:	this->labelTxBodyMotion->Text = "SHIFT_RR";		break;
				case MOTION::BODY::TURN_L:		this->labelTxBodyMotion->Text = "TURN_L";		break;
				case MOTION::BODY::TURN_LL:		this->labelTxBodyMotion->Text = "TURN_LL";		break;
				case MOTION::BODY::TURN_R:		this->labelTxBodyMotion->Text = "TURN_R";		break;
				case MOTION::BODY::TURN_RR:		this->labelTxBodyMotion->Text = "TURN_RR";		break;
				case MOTION::BODY::TURNBALL_L:	this->labelTxBodyMotion->Text = "TurnB_L";		break;
				case MOTION::BODY::TURNBALL_R:	this->labelTxBodyMotion->Text = "TurnB_R";		break;
				case MOTION::BODY::SIDE_KICK_L:	this->labelTxBodyMotion->Text = "SideK_L";		break;
				case MOTION::BODY::SIDE_KICK_R:	this->labelTxBodyMotion->Text = "SideK_R";		break;
				case MOTION::BODY::KICK_R:		this->labelTxBodyMotion->Text = "KICK_R";		break;
				case MOTION::BODY::KICK_L:		this->labelTxBodyMotion->Text = "KICK_L";		break;
				case MOTION::BODY::KICK_RR:		this->labelTxBodyMotion->Text = "KICK_RR";		break;
				case MOTION::BODY::KICK_LL:		this->labelTxBodyMotion->Text = "KICK_LL";		break;
				case MOTION::BODY::DRIBBLE_R:	this->labelTxBodyMotion->Text = "DRIBBLE_R";	break;
				case MOTION::BODY::DRIBBLE_L:	this->labelTxBodyMotion->Text = "DRIBBLE_L";	break;
				case MOTION::BODY::PICK_UP:		this->labelTxBodyMotion->Text = "PICK_UP";		break;
				case MOTION::BODY::TWIST_WAIST:	this->labelTxBodyMotion->Text = "TWIST_WAIST";	break;
				case MOTION::BODY::PUT_IN:		this->labelTxBodyMotion->Text = "PUT_IN";		break;
				case MOTION::BODY::PLACE_BALL:	this->labelTxBodyMotion->Text = "PLACE_BALL";	break;
				case MOTION::BODY::THROW:		this->labelTxBodyMotion->Text = "THROW";		break;

				//連續
				case MOTION::BODY::STOP:		this->labelTxBodyMotion->Text = "STOP";			break;
				case MOTION::BODY::SHIFT:		this->labelTxBodyMotion->Text = "SHIFT";		break;
				case MOTION::BODY::TURN:		this->labelTxBodyMotion->Text = "TURN";			break;
				case MOTION::BODY::TURNBALL:	this->labelTxBodyMotion->Text = "TURNBALL";		break;
				case MOTION::BODY::STEP:		this->labelTxBodyMotion->Text = "STEP";			break;
				case MOTION::BODY::WALK:		this->labelTxBodyMotion->Text = "WALK";			break;

				default:	this->labelTxBodyMotion->Text = System::Convert::ToString(info->serialPort.tx.data.bodyMotionCode);

				}

				//Motion Dis & Angle
				this->labelTxDis->Text = System::Convert::ToString(((unsigned short)info->serialPort.tx.data.dis-32768)/100);
				this->labelTxAngle->Text = System::Convert::ToString(((unsigned short)info->serialPort.tx.data.angle-32768)/100);
				/*printf( "TX ANGLE = %d \n", ((unsigned short)info->serialPort.tx.data.angle-32768)/100 );*/

				//Head Motion Code
				switch( info->serialPort.tx.data.headMotionCode){
				case MOTION::HEAD::STOP:		this->labelTxHeadMotion->Text = "STOP";		break;
				case MOTION::HEAD::GO_SLOW:		this->labelTxHeadMotion->Text = "GO_SLOW";	break;
				case MOTION::HEAD::GO_MIDDLE:	this->labelTxHeadMotion->Text = "GO_MIDDLE";break;
				case MOTION::HEAD::GO_FAST:		this->labelTxHeadMotion->Text = "GO_FAST";	break;
				default:	this->labelTxHeadMotion->Text = System::Convert::ToString(info->serialPort.tx.data.headMotionCode);
				}

				//Head Pos & Tilt
				this->labelTxTiltPos->Text = System::Convert::ToString(info->serialPort.tx.data.tiltPos);
				this->labelTxPanPos->Text = System::Convert::ToString(info->serialPort.tx.data.panPos);
				this->labelTxTiltPosAng->Text = System::Convert::ToString( (info->serialPort.tx.data.tiltPos-512)*300/1024 );
				this->labelTxPanPosAng->Text = System::Convert::ToString( -(info->serialPort.tx.data.panPos-512) *300/1024 );
			}
private: System::Void pictureBoxGrayLevel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

			 //決定要移動的點
			 static double dUP, dDown = 0;

			 dUP = abs( e->Y - this->vUP );
			 dDown = abs( e->Y - this->vDown );

			 int min = (int) tool.getMin(  dUP, dDown );

			 if ( min == dUP) this->vUpLineMove = true;
			 else this->vUpLineMove = false;

			 this->vLineMove = true;
		 }
private: System::Void pictureBoxGrayLevel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

			 this->labelColorVMove->Text = System::Convert::ToString( tool.pointDecimal( (double) tool.limitValue(e->Y,0,180)/180*255,0) );

			 /*---------------------------------------------------------------*/
			 if ( this->vLineMove )
			 {
				 if ( this->vUpLineMove )
					 this->vUP = tool.limitValue(e->Y,0,180);
				 else
					 this->vDown = tool.limitValue(e->Y,0,180);

				 info->vision.hsvObjRange[info->vision.objectIndex].color3.min = (int) ( (double) (180-this->vUP)/180*255 );
				 info->vision.hsvObjRange[info->vision.objectIndex].color3.max = (int) ( (double) (180-this->vDown)/180*255 );

				 this->updateObjColorLUT(info->vision.objectIndex);
				 this->updateUI(info->vision.objectIndex);
			 }

		 }
private: System::Void pictureBoxGrayLevel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->vLineMove = false;
		 }
private: System::Void buttonApply_Click(System::Object^  sender, System::EventArgs^  e) {

			 info->vision.faceregionX = System::Convert::ToInt16( this->textBox_FaceRegionX->Text );
			 info->vision.faceregionY = System::Convert::ToInt16( this->textBox_FaceRegionY->Text );
			 info->vision.faceregionHeight = System::Convert::ToInt16( this->textBox_FaceRegionHeight->Text );
			 info->vision.faceregionWidth = System::Convert::ToInt16( this->textBox_FaceRegionWidth->Text );
			 info->vision.eyeGrayTH = System::Convert::ToInt16( this->textBox_EyeGaryTH->Text );

		 }
private: System::Void buttonDetectEyeRegion_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 info->vision.initialEyeRegion = true;
			 
		 }
private: System::Void pictureBoxGaze_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

			 if ( info->isCameraOpen)
			 {
				 //右鍵：增加範圍
				 if ( e->Button == System::Windows::Forms::MouseButtons::Right )
				 {
					 //儲存點下的HSV
					 ObjectColorRange tempRange;
					 
					 tempRange.color1.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.eyefram->width+e->X)*3];
					 tempRange.color2.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.eyefram->width+e->X)*3+1];
					 tempRange.color3.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.eyefram->width+e->X)*3+2];

					 // H 更新範圍
					 if ( tempRange.color1.point-10 < 0 )
						 tempRange.color1.min = tempRange.color1.point - 10 + 256;
					 else
						 tempRange.color1.min = tempRange.color1.point - 10;

					 if ( tempRange.color1.point+10 > 255 )
						 tempRange.color1.max = tempRange.color1.point + 10 - 256;
					 else
						 tempRange.color1.max = tempRange.color1.point + 10;

					 // S 更新範圍
					 if( tempRange.color2.point-50 < 0 )
						 tempRange.color2.min = 0;
					 else
						 tempRange.color2.min = tempRange.color2.point - 50;

					 if( tempRange.color2.point+50 > 255 )
						 tempRange.color2.max = 255;
					 else
						 tempRange.color2.max = tempRange.color2.point + 50;

					 // V 更新範圍
					 if( tempRange.color3.point-50 < 0 )
						 tempRange.color3.min = 0;
					 else
						 tempRange.color3.min = tempRange.color3.point - 50;

					 if( tempRange.color3.point+50 > 255 )
						 tempRange.color3.max = 255;
					 else
						 tempRange.color3.max = tempRange.color3.point + 50;

					 //增加範圍				 
					 unsigned char minH = info->vision.hsvObjRange[info->vision.objectIndex].color1.min;
					 unsigned char maxH = info->vision.hsvObjRange[info->vision.objectIndex].color1.max;

					 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = tool.getMin(minH ,tempRange.color1.min); //System::Math::Min(minH ,tempRange.color1.min);
					 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = tool.getMax(maxH ,tempRange.color1.max); //System::Math::Max(maxH ,tempRange.color1.max);

					 // H 更新範圍
					 if ( minH > maxH || tempRange.color1.min > tempRange.color1.max )
					 {
						 if ( info->vision.hsvObjRange[info->vision.objectIndex].color1.max >= info->vision.hsvObjRange[info->vision.objectIndex].color1.min )
						 {
							 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = 0;
							 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = 255;
						 }
					 }

					 // S 更新範圍
					 if ( tempRange.color2.min < info->vision.hsvObjRange[info->vision.objectIndex].color2.min ) //比小時，右鍵小於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.min = tempRange.color2.min;
					 if ( tempRange.color2.max > info->vision.hsvObjRange[info->vision.objectIndex].color2.max ) //比大時，右鍵大於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.max = tempRange.color2.max;

					 // V 更新範圍
					 if ( tempRange.color3.min < info->vision.hsvObjRange[info->vision.objectIndex].color3.min ) //比小時，右鍵小於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.min = tempRange.color3.min;
					 if ( tempRange.color3.max > info->vision.hsvObjRange[info->vision.objectIndex].color3.max ) //比大時，右鍵大於左鍵
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.max = tempRange.color3.max;
				 }

				 //左鍵：選取範圍
				 else if ( e->Button == System::Windows::Forms::MouseButtons::Left )
				 {
					 //儲存點下的HSV
					 info->vision.hsvObjRange[info->vision.objectIndex].color1.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.eyefram->width+e->X)*3];
					 info->vision.hsvObjRange[info->vision.objectIndex].color2.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.eyefram->width+e->X)*3+1];
					 info->vision.hsvObjRange[info->vision.objectIndex].color3.point = info->vision.camFrame_HSV->imageData[(e->Y*info->vision.eyefram->width+e->X)*3+2];


					 // H 更新範圍
					 if ( info->vision.hsvObjRange[info->vision.objectIndex].color1.point-10 < 0 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = info->vision.hsvObjRange[info->vision.objectIndex].color1.point - 10 + 256;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.min = info->vision.hsvObjRange[info->vision.objectIndex].color1.point - 10;

					 if ( info->vision.hsvObjRange[info->vision.objectIndex].color1.point+10 > 255 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = info->vision.hsvObjRange[info->vision.objectIndex].color1.point + 10 - 256;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color1.max = info->vision.hsvObjRange[info->vision.objectIndex].color1.point + 10;

					 // S 更新範圍
					 if( info->vision.hsvObjRange[info->vision.objectIndex].color2.point-50 < 0 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.min = 0;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.min = info->vision.hsvObjRange[info->vision.objectIndex].color2.point - 50;

					 if( info->vision.hsvObjRange[info->vision.objectIndex].color2.point+50 > 255 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.max = 255;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color2.max = info->vision.hsvObjRange[info->vision.objectIndex].color2.point + 50;

					 // V 更新範圍
					 if( info->vision.hsvObjRange[info->vision.objectIndex].color3.point-50 < 0 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.min = 0;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.min = info->vision.hsvObjRange[info->vision.objectIndex].color3.point - 50;

					 if( info->vision.hsvObjRange[info->vision.objectIndex].color3.point+50 > 255 )
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.max = 255;
					 else
						 info->vision.hsvObjRange[info->vision.objectIndex].color3.max = info->vision.hsvObjRange[info->vision.objectIndex].color3.point + 50;
				 }


				 //更新LUT
				 this->updateObjColorLUT( info->vision.objectIndex );

				 //更新人機介面
				 this->updateUI( info->vision.objectIndex );

			 }	// end of isCamOpen or isRunSimulation
		 }
private: System::Void pictureBoxGaze_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

// 			 if ( info->isCameraOpen )
// 			 {
// 				 this->toolStripStatusLabelMousePointH->Text = System::Convert::ToString(info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3]);
// 				 this->toolStripStatusLabelMousePointS->Text = System::Convert::ToString(info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+1]);
// 				 this->toolStripStatusLabelMousePointV->Text = System::Convert::ToString(info->vision.camFrame_HSV->imageData[(e->Y*info->vision.camWidth+e->X)*3+2]);
// 			 }

		 }
private: System::Void trackBarVision_ED_Scroll(System::Object^  sender, System::EventArgs^  e) {

			 this->labelVision_EDnumbers->Text = System::Convert::ToString( (double)this->trackBarVision_ED->Value/10 );
			 info->vision.errodenumbers = (double)this->trackBarVision_ED->Value/10;
		 }
private: System::Void trackBarVision_DA_Scroll(System::Object^  sender, System::EventArgs^  e) {

			 this->labelVision_DAnumbers->Text = System::Convert::ToString( (double)this->trackBarVision_DA->Value/10 );
			 info->vision.dilatenumbers = (double)this->trackBarVision_DA->Value/10;
		 }
private: System::Void serialPortRS232_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {

			 /* TRY */
			 try
			 {
				 System::Threading::Thread::Sleep(30);

				 /* 讀取 buffer 的資料 */

				 //初始化
				 unsigned char checksum = 0;
				 array<unsigned char>^ arr = gcnew array<unsigned char>(SERIALPORT_RX_LAN*2);

				 //從buffer 抓取兩倍Rx長度的資料到 array
				 this->serialPortRS232->Read(arr ,0 ,arr->Length);		// Read the data from the port and store it in the arr 

				 //抓完後，資料存在 array ，並清空 RS232 的 Buffer
				 this->serialPortRS232->DiscardInBuffer();	

				 //列印已經收到的資料
				 // 					printf("---------------------\n");
				 // 					for (int i=0 ;i<i+SERIALPORT_RX_LAN ;i++) {	printf( "%d  " ,arr[i] ); }
				 // 					printf("---------------------\n");

				 /* 從array抓取我們真正要的資料 */

				 //先找檔頭 (利用 startCode 確認檔頭位置)
				 for (int i=0 ;i<SERIALPORT_RX_LAN*2 ;i++)
				 {

					 //檔頭確認 ok，開始以此為頭，抓取 Rx 長度的資料
					 if ( arr[i]==255 && arr[i+1]==254 )
					 {
						 //計算 checkSum
						 checksum = 0;
						 for ( int j=i+2 ;j<i+SERIALPORT_RX_LAN-1 ;j++ ) { checksum += arr[j]; }
						 checksum = ~(checksum); //加總完，要取補數

						 //checkSum 確認 OK，開始接著確認其他部分
						 if ( checksum == arr[i+SERIALPORT_RX_LAN-1] )
						 {
							 //存入之前先檢查有無不合理的值，盡量過濾掉板子的BUG
							 if ( (arr[i+3]+arr[i+4]*256)>1024 || (arr[i+5]+arr[i+6]*256)>1024 )
							 {
								 //頭部錯誤，列印錯誤
								 printf("--- BOARD ERROR ---\n");										
								 for (int i=0 ;i<i+SERIALPORT_RX_LAN ;i++) { printf( "%d  " ,arr[i] ); }
								 printf("--- END OF BOARD ERROR ---\n");
								 break;	//跳出迴圈
							 } // END OF 頭部錯誤

							 //確定沒錯以後，就將板子送進來的訊號存起來
							 for (int j=i ;j<i+SERIALPORT_RX_LAN ;j++) {	
								 info->serialPort.rx.arr[j-i] = arr[j];

							 }

							 info->serialPort.rx.data.waistPosRoll = 2048;

							 // 								if ( info->serialPort.rx.data.dip < 100 )
							 // 								{
							 // 									info->subEventIndex = info->serialPort.rx.data.dip >> 4;
							 // 									info->serialPort.rx.data.dip &= 0x0f;
							 // 								}
							 break;

						 } // END OF 確認 checkSum = true

						 else
						 {
							 printf("--- CHECKSUM ERROR ---\n");
							 for (int i=0 ;i<i+SERIALPORT_RX_LAN ;i++) { printf( "%d  " ,arr[i] ); }
							 printf("--- END OF CHECKSUM ERROR ---\n");
						 } // END OF 確認 checkSum = false

					 } //END OF 找檔頭 


				 } //END OF FOR LOOP 

			 } // END OF TRY

			 catch(...)
			 {
				 printf("\n RS232 ERROR\n");
			 }
		 }

};
}

