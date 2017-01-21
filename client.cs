using System;
using System.Threading;
using System.Drawing;

// Before using this code you need to add a reference to the Surfer.exe program,
// which will automatically cause a type library to be generated.
// 1. In Visual Studio .NET, open the Solution Explorer
// 2. Right-click on References and select "Add Reference"
// 3. Click "Browse", find Surfer.exe and click "Open"
// 4. Click OK
// You can all add "using Surfer;" to the top of this file to to avoid having to
// reference the Server namespace on declarations.
//
//

namespace TT
{
	/// <summary>
	/// Demonstrates how to control surfer from a C# class
	/// </summary>
	public class SurferControl {
		public Surfer.IColorMap ColorMap;

		public SurferControl() {
			//
			// TODO: Add constructor logic here
			//
			// Make an instance of the application
			Surfer.ApplicationClass AppSurfer = new Surfer.ApplicationClass();

			// Make the application visible
			AppSurfer.Visible = true;

			// Get the Documents collection
			Surfer.IDocuments Docs = AppSurfer.Documents;

			// Add a new document to the Documents collection
			Surfer.IPlotDocument Doc = (Surfer.IPlotDocument) Docs.Add(Surfer.SrfDocTypes.srfDocPlot);

			// Get the Shapes collection from the document
			Surfer.IShapes Shapes = Doc.Shapes;

			// Create a shaded relief map from the helens2.grd file
			Surfer.IMapFrame MapFrame = Shapes.AddReliefMap(AppSurfer.Path + @"\samples\helens2.grd");

			// Get the shaded relief overlay from the map frame
			Surfer.IReliefMap ReliefMap = (Surfer.IReliefMap) MapFrame.Overlays.Item(1);

			// Get the ColorMap used by the relief map
			ColorMap = ReliefMap.ColorMap;

			// Animate the colors of the shaded relief map from the default black to red.
			Thread AnimateThread = new Thread(new ThreadStart(AnimateColorMap));
			AnimateThread.Start();

		}
		void AnimateColorMap() {
			
			Array ColorArray = ColorMap.NodeColors;
			Array Positions  = ColorMap.NodePositions;

			for (int iRed=0; iRed<=255; iRed += 51) {
				Color color = Color.FromArgb(0, 0, iRed);
				ColorArray.SetValue(color.ToArgb(), 0);
				ColorMap.SetNodes(Positions, ColorArray);

				Thread.Sleep(1000);
			}
		}

	}
}
