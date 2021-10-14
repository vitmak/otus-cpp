#include "Controller.h"
#include "View.h"


//void OnCreateNewDocument(GraphicEditorApp& graphicEditor) {
//	graphicEditor.CreateNewDocument();
//}
//
//void OnImportDocument(GraphicEditorApp& graphicEditor) {
//	FilePathDlg dlg;
//
//	// Get file path from dialog
//	std::string path;
//	graphicEditor.ImportDocument(path);
//}
//
//void OnExportDocument(GraphicEditorApp& graphicEditor) {
//	FilePathDlg dlg;
//
//	// Get file path from dialog
//	std::string path;
//	graphicEditor.ExportDocument(path);
//}
//
//void OnCreatePrimitive(GraphicEditorApp& graphicEditor) {
//	PrimitiveDetailsDlg dlg;
//
//	// ...
//	auto selectedShapeType = PrimitiveTypes::eLine;
//	graphicEditor.CreatePrimitive(selectedShapeType);
//}
//
//void OnDeletePrimitive(GraphicEditorApp& graphicEditor) {
//	graphicEditor.DeletePrimitive();
//}

int main() {
	GraphicEditorApp graphicEditor;

	auto OnCreateNewDocument = [&graphicEditor]() {
		graphicEditor.CreateNewDocument();
	};

	auto OnImportDocument = [&graphicEditor]() {
		FilePathDlg dlg;

		// Get file path from dialog
		std::string path;
		graphicEditor.ImportDocument(path);
	};

	auto OnExportDocument = [&graphicEditor]() {
		FilePathDlg dlg;

		// Get file path from dialog
		std::string path;
		graphicEditor.ExportDocument(path);
	};

	auto OnCreatePrimitive = [&graphicEditor]() {
		PrimitiveDetailsDlg dlg;

		// ...
		auto selectedShapeType = PrimitiveTypes::eLine;
		graphicEditor.CreatePrimitive(selectedShapeType);
	};

	auto OnDeletePrimitive = [&graphicEditor]() {
		graphicEditor.DeletePrimitive();
	};


	auto menuBar = graphicEditor.GetFrame().GetMenu();
	menuBar.SetCommand("Create New", OnCreateNewDocument);
	menuBar.SetCommand("Import Document", OnImportDocument);
	menuBar.SetCommand("Export Document", OnExportDocument);
	menuBar.SetCommand("Create primitive", OnCreatePrimitive);
	menuBar.SetCommand("Delete primitive", OnDeletePrimitive);

	menuBar.OnClick("Create New");
	menuBar.OnClick("Create primitive");
	menuBar.OnClick("Export Document");
	
	menuBar.OnClick("Import Document");
	
	menuBar.OnClick("Select primitives");
	auto canvas = graphicEditor.GetFrame().GetCanvas();
	canvas.OnMouseClick(100, 100);

	menuBar.OnClick("Delete primitive");
	menuBar.OnClick("Export Document");
}