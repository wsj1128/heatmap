using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Surfer;

namespace heatmap
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
            // Make an instance of the application
            Surfer.Application AppSurfer = new Surfer.Application();

            //AppSurfer.Visible = false;           //注Surfer窗口是不显现
            //AppSurfer.WindowState = Surfer.SrfWindowState.srfWindowStateMinimized;

            AppSurfer.Caption = "雨量分布图";
            //AppSurfer.ScreenUpdating = false;  //Surfer制图过程是否显示

            //Application app = new Application();
            var path = AppDomain.CurrentDomain.BaseDirectory;
            AppSurfer.GridData2(DataFile: path + "456.xlsx",          //数据文件地址
                xCol: 1,                                        //x为第一列数据
                yCol: 2,                                        //y为第二列数据
                zCol: 3,                                        //z为第三列数据                             
                Algorithm: SrfGridAlgorithm.srfKriging,

                OutGrid: path + "456.grd",                     //返回文件为gridfile
                OutFmt: Surfer.SrfGridFormat.srfGridFmtAscii);  //返回文件编码为Ascii
            AppSurfer.Quit();
            System.GC.Collect(System.GC.GetGeneration(AppSurfer));

            // Get the Documents collection
            IDocuments docs = AppSurfer.Documents;
            // Add a new document to the Documents collection
            IPlotDocument Doc = (IPlotDocument)docs.Add(SrfDocTypes.srfDocPlot);    //创建一个空白绘图文档
            // Get the Shapes collection from the document
            IShapes Shapes = Doc.Shapes;
            //var path = AppDomain.CurrentDomain.BaseDirectory;

            #region 添加等值面
            IMapFrame contourMapFrame = Shapes.AddContourMap(path + "456.grd");    //加载网格文件
            contourMapFrame.Axes.Item(2).MajorTickLength = 0;
            contourMapFrame.Axes.Item(4).MajorTickLength = 0;
            
            
            /*
            for (int i = 1; i <= contourMapFrame.Axes.Count; i++)
            {
                contourMapFrame.Axes.Item(i).Visible = false;
                contourMapFrame.Axes.Item(i).MajorTickType = SrfTickType.srfTickNone;
                contourMapFrame.Axes.Item(i).ShowLabels = false;
            }
            */
            /*
            contourMapFrame.SetLimits(xMin: 117.742635, //x最小值
                            xMax: 122.452486,           //x最大者
                            yMin: 29.418809,            //y最小值
                            yMax: 32.463007             //y最大值
            );
            */
            contourMapFrame.xMapPerPU = 0.8;           //设置比例
            //contourMapFrame.yMapPerPU = 0.25;           //设置比例
            
            IContourMap contourMap = (IContourMap)contourMapFrame.Overlays.Item(1);

            
            
            contourMap.Levels.AutoGenerate(contourMap.Grid.zMin, 40, 0.5);
            //contourMap.Levels.
            contourMap.ShowColorScale = true;                                     // 显示对应色柱
            //contourMap.ColorScale.Top = contourMap.Top;                           //柱y方向位置
            //contourMap.ColorScale.Left = contourMap.Left + contourMap.Width + 2;//色柱x方向位置
            //contourMap.ColorScale.Width = 0.5;                                    //色柱宽度
            //contourMap.ColorScale.Height = contourMap.Height;                                     //色柱高度
            //contourMap.ColorScale.FirstLabel = 2;
            contourMap.ColorScale.LabelFrequency = 10;
            
            
        
            Surfer.IText Text1 = Doc.Shapes.AddText(contourMapFrame.Left + 1, contourMapFrame.Top + 0.2, "市雨量分布图");
            Text1.Font.Size = 24;
            Text1.Font.Face = @"宋体";
            contourMap.FillContours = true;//绘制等值线；添加颜色填充                                          

            //加载系统颜色
            contourMap.FillForegroundColorMap.LoadFile(path + "BlueRed1.clr");
            //contourMap.
            //contourMap.ApplyFillToLevels            
            contourMap.FillForegroundColorMap.SetDataLimits(0,40);
            contourMap.ApplyFillToLevels(1, 1, 0);
            //使用灰色


            for (int i = 0; i < contourMap.Levels.Count; i++)
                        {
                          //  contourMap.Levels.Item(i + 1).ShowLabel = true;                 //显示等值线上的数值
                          //  contourMap.Levels.Item(i + 1).ShowHach = false;                 //
                            contourMap.Levels.Item(i + 1).Line.Style = "Invisible";         //不显示线
                        }
            
            contourMap.SmoothContours = SrfConSmoothType.srfConSmoothNone;   //平滑等值线边界当前设置不平滑
            #endregion


            #region 添加边界
            //后添加的会覆盖在先前添加的图片之上
            /*
                    IMapFrame boundryMapFrame = Shapes.AddBaseMap(path + "123.bln", "Defaults=1");
                    for (int i = 1; i <= boundryMapFrame.Axes.Count; i++)
                    {
                        boundryMapFrame.Axes.Item(i).Visible = true;                           //隐藏轴线
                        boundryMapFrame.Axes.Item(i).MajorTickType = SrfTickType.srfTickNone;   //隐藏边线
                        boundryMapFrame.Axes.Item(i).ShowLabels = true;                        //隐藏轴线上的坐标
                    }
                    boundryMapFrame.SetLimits(xMin: 117.742635, //x最小值
                                    xMax: 122.452486,           //x最大者
                                    yMin: 29.418809,            //y最小值
                                    yMax: 32.463007             //y最大值
                    );
                    boundryMapFrame.xMapPerPU = 0.25;
                    boundryMapFrame.yMapPerPU = 0.25;

                    IBaseMap boundryBaseMap = (IBaseMap)boundryMapFrame.Overlays.Item(1);
                    boundryBaseMap.Line.Width = 0.01;           //设置边线宽度
                  */ 
            #endregion

            string strWH = string.Format("width = {0:f0}, height = {1:f0}, KeepAspect = 1, ColorDepth = 32", 800, 450);//设置输出图片的高度和宽度
            Doc.Export2(path + "Image.png", SelectionOnly: false);//设置输出图片格式名
            Doc.Close(SrfSaveTypes.srfSaveChangesNo);   //不生成srf文件
            AppSurfer.Quit();
            System.GC.Collect(System.GC.GetGeneration(AppSurfer));

            int h = 20;

            Image bmp = new Bitmap("Image.png");
            Image newbmp = new Bitmap(bmp.Width, bmp.Height + h);
            //Image NewImage = image.GetThumbnailImage(image.Width,image.Height + 50,null,new IntPtr());
            //Graphics g = Graphics.FromImage(NewImage);
            //g.DrawImage(NewImage, 0, NewImage.Height, NewImage.Width, NewImage.Height);

            //NewImage.Save("Image1.png");
            Graphics g = Graphics.FromImage(newbmp);
            g.DrawImage(bmp, 0, 0);    
            
            Rectangle rect = new Rectangle(0, bmp.Height, bmp.Width, h);
            
            
            String str = "hello, string";
            Font font = new Font("宋体", 8);
            SolidBrush sbrush = new SolidBrush(Color.Black);
            //Pen blackPen = new Pen(Color.White, 3);
            //g.DrawRectangle(blackPen ,rect);
            SolidBrush wbrush = new SolidBrush(Color.White);

            g.FillRectangle(wbrush,rect);

            g.DrawString(str, font, sbrush, rect);
            
            newbmp.Save("Image1.png");

            pictureBox1.Image = Image.FromFile("Image1.png");
            //调整窗口大小
            this.Width = newbmp.Width;
            this.Height = newbmp.Height;

        }

        

    }
}
