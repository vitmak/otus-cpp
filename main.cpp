#include "Controller.h"


int main() {
	GraphicEditorApp graphicEdtitorApp;

	graphicEdtitorApp.CreateNewDocument();
	graphicEdtitorApp.CreatePrimitive(PrimitiveTypes::eCircle);
	graphicEdtitorApp.CreatePrimitive(PrimitiveTypes::eLine);

	graphicEdtitorApp.ExportDocument("BusinessCard");

	// TODO: Select shape with mouse click
	graphicEdtitorApp.DeletePrimitive();

	graphicEdtitorApp.ExportDocument("BusinessCard2");

	graphicEdtitorApp.ImportDocument("TestPicture");
}