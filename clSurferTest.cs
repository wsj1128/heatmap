using System;
using System.Threading;
using System.Drawing;
using System.Collections;
using System.IO;
using Surfer;

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

namespace nsSurferTest
{
	/// <summary>
	///----------------------------------------------------------------------------------------
	///  Class Name: clSurferTest
	///
	///  Purpose: Basic code to access the Surfer object using .NET C#
	///  
	///  This is just a start.  There is much more to learn.
	///	
	///----------------------------------------------------------------------------------------
	/// 01/23/2007
	/// Code converted to C# by Eric Grimnes (Grimnes and Associates - www.grimnes.com) with assistance 
	/// from Tom Bresnahan (Golden Software Inc. - www.goldensoftware.com) etal. Thanks Tom
	///----------------------------------------------------------------------------------------
	/// </summary>

	public class clSurferTest
	{
		public clSurferTest() 
		{
		}
		
		public void DisplayGraph() 
		{
			string path = @"C:\Program Files\Golden Software\Surfer8\Samples\";
			string datfile1 = path + "csharp_test.DAT";
			string grdfile1 = path + "csharp_test.GRD";
			
			//*** Example of csharp_test.DAT ***//

			//"Count","Value1","Value2"
			//0,0,2
			//0,1,0
			//0,2,0
			//0,3,6
			//0,4,3
			//0,5,7
			//0,6,10
			//0,7,6

			// Make an instance of the application
			Surfer.ApplicationClass AppSurfer = new Surfer.ApplicationClass();

			// Make the application visible
			AppSurfer.Visible = true;
			AppSurfer.WindowState = Surfer.SrfWindowState.srfWindowStateNormal;
			AppSurfer.Width = 800;
			AppSurfer.Height = 600;

			// Get the Documents collection
			Surfer.IDocuments Docs = AppSurfer.Documents;

			// Add a new document to the Documents collection
			Surfer.IPlotDocument Doc = (Surfer.IPlotDocument) Docs.Add(Surfer.SrfDocTypes.srfDocPlot);

			// Get the Shapes collection from the document
			Surfer.IShapes Shapes = Doc.Shapes;

			AppSurfer.GridData(datfile1, 1, 2, 3, 
				System.Type.Missing, System.Type.Missing, System.Type.Missing, 
				System.Type.Missing, System.Type.Missing, System.Type.Missing, 
				System.Type.Missing, System.Type.Missing, System.Type.Missing, 
				System.Type.Missing, Surfer.SrfGridAlgorithm.srfKriging, false, 
				System.Type.Missing, System.Type.Missing, System.Type.Missing, 
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing, 
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				grdfile1, Surfer.SrfGridFormat.srfGridFmtS7, 
				System.Type.Missing, System.Type.Missing, System.Type.Missing,
				System.Type.Missing, System.Type.Missing, System.Type.Missing);

			Surfer.IMapFrame MapFrame = Shapes.AddContourMap(grdfile1);
		}
	}
}