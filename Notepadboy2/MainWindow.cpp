#include "MainWindow.h"
#include <QFile>
#include <QFileDialog>
#include <QFontDatabase>
#include <QMessageBox>
#include <QTextStream>
#include <QWebChannel>
#include <QTextDocumentFragment>
#include "previewpage.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//ui.editor->setText("yolo");
	ui.preview->setContextMenuPolicy(Qt::NoContextMenu);
	PreviewPage * page = new PreviewPage(this);
	ui.preview->setPage(page);
	connect(ui.editor, &QPlainTextEdit::textChanged, [this]() {
		m_content.setText(ui.editor->toPlainText()); 
		});
	QWebChannel * channel = new QWebChannel(this);
	channel->registerObject(QStringLiteral("content"), &m_content);
	page->setWebChannel(channel);
	ui.preview->setUrl(QUrl("qrc:/MainWindow/resources/index.html"));
	
	

}
void MainWindow::on_actionSave_As_triggered() {
	QString file_path = QFileDialog::getSaveFileName(this,
		tr("Save MarkDown File"), "", tr("MarkDown File (*.md *.markdown)"));
	if (file_path.isEmpty())
		return;
	path = file_path;
	on_actionSave_triggered();
}
void MainWindow::on_actionBold_triggered() {
	auto cursor = ui.editor->textCursor();
	if (cursor.selectedText().isEmpty()) {
		cursor.insertText("**Insert Text Here**");
	}
	else {
		auto frag = cursor.selection();
		auto qstr =  frag.toPlainText();
		auto stdstr = qstr.toStdString();
		size_t loc = stdstr.find("**");
		if (loc != std::string::npos) {
			stdstr.erase(loc, loc + 2);
			size_t loc2 = stdstr.find_last_of("**");
			if(loc2 != std::string::npos)
			stdstr.erase(loc2-1, loc2 );
			if (loc != 0) {
				stdstr = "**" + stdstr + "**";
			}
			auto qstr2 = qstr.fromStdString(stdstr);
			
			auto newfrag = frag.fromPlainText(qstr2);
			cursor.insertFragment(newfrag);
			return;
		}
		else {
			qstr = "**" + qstr + "**";
			auto newfrag = frag.fromPlainText(qstr);
			cursor.insertFragment(newfrag);
		}
	}

}
void MainWindow::on_actionSave_triggered() {
	if (path.isEmpty()) {
		on_actionSave_As_triggered();
		return;
	}
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::warning(this, windowTitle(), tr("Could not write file to %1: %2").arg(QDir::toNativeSeparators(path), file.errorString()));
		return;
	}

	QTextStream txtout(&file);
	txtout.setCodec("UTF-8");
	txtout << ui.editor->toPlainText();
	file.close();
	return;
}