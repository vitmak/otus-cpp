#include "Controller.h"
#include "View.h"


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

	auto OnCanvasClick = [&graphicEditor](int x, int y) {
		graphicEditor.SelectPrimitive(x, y);
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
	canvas->SetCommand(OnCanvasClick);
	canvas->OnMouseClick(100, 100);

	menuBar.OnClick("Delete primitive");
	menuBar.OnClick("Export Document");
}
