using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using Surfer;


namespace AppSurfer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string strFolder = @"d:\AppSurfer\content";
        string OutGrpahic = @"d:\AppSurfer\outrain.bmp";
        

        private void button1_Click(object sender, EventArgs e)
        {
            string DataFile = strFolder + @"/rain.txt";
            string OutGrid = strFolder + @"/grid_rain.grd";
            string SmoothGrid = strFolder + @"/smooth_rain.grd";
            string BlankFile = strFolder + @"/市边界.bln";
            string BlankedGrid = strFolder + @"/blank_rain.grd";
            string BaseFile = strFolder + @"/市底图.bln";
            string PoseFile = strFolder + @"/站名.dat";
            string LevelFile = strFolder + @"/雨量色标.lvl";

            Surfer.Application AppSurfer = new Surfer.Application();     //对Surfer的调用
            AppSurfer.Visible = false;           //注Surfer窗口是不显现
            AppSurfer.WindowState = Surfer.SrfWindowState.srfWindowStateMinimized;

            AppSurfer.Caption = "百色市雨量分布图";
            AppSurfer.ScreenUpdating = false;  //Surfer制图过程是否显示

                        
            AppSurfer.GridData(DataFile, 1, 2, 3, Type.Missing, Surfer.SrfDupMethod.srfDupNone, 0.03, 0.03, Type.Missing, Type.Missing,
                                104.3, 108.1, 22.75, 25.2, Surfer.SrfGridAlgorithm.srfKriging, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                               Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                                Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                               Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, OutGrid, Surfer.SrfGridFormat.srfGridFmtAscii,
                                 Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing);
            
            /*注:将所提供的降水文件格点化, DataFile即需要格点化的文件名加路径,文件第1列是经度,第2列是纬度,第3列是降水量值,网格经纬向的分
            辨率都是0. 03,起始经度是104.3度,终止经度是108.1度,起始纬度是22.75度,终止纬度是25.2度,选择的插值方法是Kriging方法, GridFile即时离散插值后生
            成的路径加文件名(其后缀应该是“. grd”, . grd文件格式是Ascii码的形式;*/

            
            AppSurfer.GridSplineSmooth(OutGrid, 8, 8, SrfSplineMethod.srfSplineInsert, SmoothGrid, SrfGridFormat.srfGridFmtAscii);
            /*注:OutGrid为输入的格点化文件路径加文件名,将其进行平滑，平滑方法为Insert，行列的插值点数都设为8,SmoothGrid为输出的格点化文件路径加文件
            名,其输出格式也是Ascii码;*/

            AppSurfer.GridBlank(SmoothGrid, BlankFile, BlankedGrid, Surfer.SrfGridFormat.srfGridFmtAscii);
            /*注:第一个GridFile为输入的格点化文件路径加文件名,将其利用bln文件去掉边界外的数据,BlankedGrid为输出的格点化文件路径加文件
            名,其输出格式也是Ascii码;*/
                   
                        
            Surfer.IPlotDocument Doc = (Surfer.IPlotDocument)AppSurfer.Documents.Add(Surfer.SrfDocTypes.srfDocPlot);
            //建立一个绘图文档和一个绘图窗口

            Surfer.IMapFrame mapframe = Doc.Shapes.AddContourMap(BlankedGrid);
            //注:添加等值面图层MapFrame，将BlankedGrid格点化文件生成等值线图;

            mapframe.Axes.Item(1).Visible = false;
            mapframe.Axes.Item(2).Visible = false;
            mapframe.Axes.Item(3).Visible = false;
            mapframe.Axes.Item(4).Visible = false;
            //注:不显示标注图的横纵坐标轴

            
            Surfer.IContourMap ClassedCounterMap = (Surfer.IContourMap)mapframe.Overlays.Item(1);
            //注:将等值线图形属性指定给变量ClassedCounterMap;

            ClassedCounterMap.Levels.LoadFile(LevelFile);  //注:等值线图的色彩填充文件为LevelFile,
            ClassedCounterMap.FillContours = true;         //绘制等值线；
            ClassedCounterMap.ShowColorScale = true;       //显示色标条；
            ClassedCounterMap.SmoothContours = SrfConSmoothType.srfConSmoothHigh;  //SmoothContours为平滑等值线边界

            ClassedCounterMap.ColorScale.Height = 1.4;
            ClassedCounterMap.ColorScale.Width = 0.3;
            ClassedCounterMap.ColorScale.Left = ClassedCounterMap.Left + 0.3;
            ClassedCounterMap.ColorScale.Top = ClassedCounterMap.Top - 2.5;
            ClassedCounterMap.ColorScale.LabelFont.Size = 12;
            //注:对色标条进行设置

            Surfer.IText Text1 = Doc.Shapes.AddText(ClassedCounterMap.Left + 0.2, ClassedCounterMap.Top, "市雨量分布图");
            Text1.Font.Size = 12;
            Surfer.IText Text2 = Doc.Shapes.AddText(ClassedCounterMap.Left + 0.3, ClassedCounterMap.Top - 2.3, "图例");
            Text1.Font.Size = 12;
            //添加文本文件


            Surfer.IMapFrame mapframe1 = Doc.Shapes.AddPostMap(PoseFile, 1, 2, 3, 0, 0);
            /*新建一个给地图添加标注文件的图层,PoseFile就是标注文件的路径加文件名, 1代表文件中经度, 2代表纬度,
             3代表第3列是需要标注的名称, 0表示所需要选用的符号, 0是标注选用的角度;*/

            mapframe1.Axes.Item(1).Visible = false;
            mapframe1.Axes.Item(2).Visible = false;
            mapframe1.Axes.Item(3).Visible = false;
            mapframe1.Axes.Item(4).Visible = false;
            
            Surfer.IPostMap PostMap = (Surfer.IPostMap)mapframe1.Overlays.Item(1);
            PostMap.LabelFont.Face = @"宋体";
            PostMap.LabelFont.Size = 9;
            PostMap.LabelFont.Bold = true;
            PostMap.Symbol.Size = 0.01;
            
            Surfer.IMapFrame mapframe2 = Doc.Shapes.AddBaseMap(BaseFile);
            //添加底图文件
                        
            Doc.Shapes.SelectAll();
            Surfer.ISelection sel = Doc.Selection;
            sel.OverlayMaps();
            //注:将图层全部选定,进行层叠覆盖;

            ((Surfer.IMapFrame)Doc.Shapes.Item("Map")).SetLimits(104.5, 107.9, 22.8, 25.2);

            Doc.Export(OutGrpahic, false, "Defaults=1,width=800,KeepAspect=1,ColorDepth=24,Automatic=0,Quality=100");
            //注:输出文件加路径名是OutGraphic,即图片名称,可以选择几种后缀(如png、jpg等) ,定义图片的大小、颜色、质量等等
              
            File.Delete(OutGrid);
            File.Delete(SmoothGrid);
            File.Delete(BlankedGrid);
            //删除临时文件 

            AppSurfer.Documents.CloseAll(Surfer.SrfSaveTypes.srfSaveChangesNo);
            AppSurfer.Quit();
            //退出AppSurfer; 

            pictureBox1.Image = Image.FromFile(OutGrpahic);
            //把绘制好的雨量图显示在pictureBox1上；

        }
    }
}