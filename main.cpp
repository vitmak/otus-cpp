#include "Controller.h"



int main() {
	GraphicEditorApp graphicEdtitorApp;

	graphicEdtitorApp.CreateNewDocument();
	graphicEdtitorApp.CreatePrimitive(PrimitiveTypes::eCircle, 0/*primitive ID*/);
	graphicEdtitorApp.CreatePrimitive(PrimitiveTypes::eLine, 1);

	graphicEdtitorApp.ExportDocument("BusinessCard");

	// TODO: Select shape with mouse click
	//auto primitivePtr = graphicEdtitorApp.SelectPrimitive(1/*Select the line*/);
	graphicEdtitorApp.DeletePrimitive();

	graphicEdtitorApp.ExportDocument("BusinessCard2");

	graphicEdtitorApp.ImportDocument("TestPicture");
}