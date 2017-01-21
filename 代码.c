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
            string BlankFile = strFolder + @"/�б߽�.bln";
            string BlankedGrid = strFolder + @"/blank_rain.grd";
            string BaseFile = strFolder + @"/�е�ͼ.bln";
            string PoseFile = strFolder + @"/վ��.dat";
            string LevelFile = strFolder + @"/����ɫ��.lvl";

            Surfer.Application AppSurfer = new Surfer.Application();     //��Surfer�ĵ���
            AppSurfer.Visible = false;           //עSurfer�����ǲ�����
            AppSurfer.WindowState = Surfer.SrfWindowState.srfWindowStateMinimized;

            AppSurfer.Caption = "��ɫ�������ֲ�ͼ";
            AppSurfer.ScreenUpdating = false;  //Surfer��ͼ�����Ƿ���ʾ

                        
            AppSurfer.GridData(DataFile, 1, 2, 3, Type.Missing, Surfer.SrfDupMethod.srfDupNone, 0.03, 0.03, Type.Missing, Type.Missing,
                                104.3, 108.1, 22.75, 25.2, Surfer.SrfGridAlgorithm.srfKriging, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                               Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                                Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                               Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, OutGrid, Surfer.SrfGridFormat.srfGridFmtAscii,
                                 Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing);
            
            /*ע:�����ṩ�Ľ�ˮ�ļ���㻯, DataFile����Ҫ��㻯���ļ�����·��,�ļ���1���Ǿ���,��2����γ��,��3���ǽ�ˮ��ֵ,����γ��ķ�
            ���ʶ���0. 03,��ʼ������104.3��,��ֹ������108.1��,��ʼγ����22.75��,��ֹγ����25.2��,ѡ��Ĳ�ֵ������Kriging����, GridFile��ʱ��ɢ��ֵ����
            �ɵ�·�����ļ���(���׺Ӧ���ǡ�. grd��, . grd�ļ���ʽ��Ascii�����ʽ;*/

            
            AppSurfer.GridSplineSmooth(OutGrid, 8, 8, SrfSplineMethod.srfSplineInsert, SmoothGrid, SrfGridFormat.srfGridFmtAscii);
            /*ע:OutGridΪ����ĸ�㻯�ļ�·�����ļ���,�������ƽ����ƽ������ΪInsert�����еĲ�ֵ��������Ϊ8,SmoothGridΪ����ĸ�㻯�ļ�·�����ļ�
            ��,�������ʽҲ��Ascii��;*/

            AppSurfer.GridBlank(SmoothGrid, BlankFile, BlankedGrid, Surfer.SrfGridFormat.srfGridFmtAscii);
            /*ע:��һ��GridFileΪ����ĸ�㻯�ļ�·�����ļ���,��������bln�ļ�ȥ���߽��������,BlankedGridΪ����ĸ�㻯�ļ�·�����ļ�
            ��,�������ʽҲ��Ascii��;*/
                   
                        
            Surfer.IPlotDocument Doc = (Surfer.IPlotDocument)AppSurfer.Documents.Add(Surfer.SrfDocTypes.srfDocPlot);
            //����һ����ͼ�ĵ���һ����ͼ����

            Surfer.IMapFrame mapframe = Doc.Shapes.AddContourMap(BlankedGrid);
            //ע:��ӵ�ֵ��ͼ��MapFrame����BlankedGrid��㻯�ļ����ɵ�ֵ��ͼ;

            mapframe.Axes.Item(1).Visible = false;
            mapframe.Axes.Item(2).Visible = false;
            mapframe.Axes.Item(3).Visible = false;
            mapframe.Axes.Item(4).Visible = false;
            //ע:����ʾ��עͼ�ĺ���������

            
            Surfer.IContourMap ClassedCounterMap = (Surfer.IContourMap)mapframe.Overlays.Item(1);
            //ע:����ֵ��ͼ������ָ��������ClassedCounterMap;

            ClassedCounterMap.Levels.LoadFile(LevelFile);  //ע:��ֵ��ͼ��ɫ������ļ�ΪLevelFile,
            ClassedCounterMap.FillContours = true;         //���Ƶ�ֵ�ߣ�
            ClassedCounterMap.ShowColorScale = true;       //��ʾɫ������
            ClassedCounterMap.SmoothContours = SrfConSmoothType.srfConSmoothHigh;  //SmoothContoursΪƽ����ֵ�߽߱�

            ClassedCounterMap.ColorScale.Height = 1.4;
            ClassedCounterMap.ColorScale.Width = 0.3;
            ClassedCounterMap.ColorScale.Left = ClassedCounterMap.Left + 0.3;
            ClassedCounterMap.ColorScale.Top = ClassedCounterMap.Top - 2.5;
            ClassedCounterMap.ColorScale.LabelFont.Size = 12;
            //ע:��ɫ������������

            Surfer.IText Text1 = Doc.Shapes.AddText(ClassedCounterMap.Left + 0.2, ClassedCounterMap.Top, "�������ֲ�ͼ");
            Text1.Font.Size = 12;
            Surfer.IText Text2 = Doc.Shapes.AddText(ClassedCounterMap.Left + 0.3, ClassedCounterMap.Top - 2.3, "ͼ��");
            Text1.Font.Size = 12;
            //����ı��ļ�


            Surfer.IMapFrame mapframe1 = Doc.Shapes.AddPostMap(PoseFile, 1, 2, 3, 0, 0);
            /*�½�һ������ͼ��ӱ�ע�ļ���ͼ��,PoseFile���Ǳ�ע�ļ���·�����ļ���, 1�����ļ��о���, 2����γ��,
             3�����3������Ҫ��ע������, 0��ʾ����Ҫѡ�õķ���, 0�Ǳ�עѡ�õĽǶ�;*/

            mapframe1.Axes.Item(1).Visible = false;
            mapframe1.Axes.Item(2).Visible = false;
            mapframe1.Axes.Item(3).Visible = false;
            mapframe1.Axes.Item(4).Visible = false;
            
            Surfer.IPostMap PostMap = (Surfer.IPostMap)mapframe1.Overlays.Item(1);
            PostMap.LabelFont.Face = @"����";
            PostMap.LabelFont.Size = 9;
            PostMap.LabelFont.Bold = true;
            PostMap.Symbol.Size = 0.01;
            
            Surfer.IMapFrame mapframe2 = Doc.Shapes.AddBaseMap(BaseFile);
            //��ӵ�ͼ�ļ�
                        
            Doc.Shapes.SelectAll();
            Surfer.ISelection sel = Doc.Selection;
            sel.OverlayMaps();
            //ע:��ͼ��ȫ��ѡ��,���в������;

            ((Surfer.IMapFrame)Doc.Shapes.Item("Map")).SetLimits(104.5, 107.9, 22.8, 25.2);

            Doc.Export(OutGrpahic, false, "Defaults=1,width=800,KeepAspect=1,ColorDepth=24,Automatic=0,Quality=100");
            //ע:����ļ���·������OutGraphic,��ͼƬ����,����ѡ���ֺ�׺(��png��jpg��) ,����ͼƬ�Ĵ�С����ɫ�������ȵ�
              
            File.Delete(OutGrid);
            File.Delete(SmoothGrid);
            File.Delete(BlankedGrid);
            //ɾ����ʱ�ļ� 

            AppSurfer.Documents.CloseAll(Surfer.SrfSaveTypes.srfSaveChangesNo);
            AppSurfer.Quit();
            //�˳�AppSurfer; 

            pictureBox1.Image = Image.FromFile(OutGrpahic);
            //�ѻ��ƺõ�����ͼ��ʾ��pictureBox1�ϣ�

        }
    }
}