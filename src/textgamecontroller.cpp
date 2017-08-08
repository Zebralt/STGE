
#include "textgamecontroller.h"
#include "textgame.h"
#include "mktohtml/mk.h"

/// CONTROLLER

TextGameController::TextGameController(QObject* p) : master(new TextGame()), QObject(p) {

}

void TextGameController::proceed(const QString& str) {

    if (master) master->proceed(str.toStdString());

    emit choicesChanged();
    emit sceneChanged();
    emit previousSceneChanged();
    emit sceneTitleChanged();
}

void TextGameController::initialize() {
  if (master) master->initialize();

  emit choicesChanged();
  emit sceneChanged();
  emit previousSceneChanged();
  emit sceneTitleChanged();
}

void TextGameController::loadSavedGame(const QString& path) {

}

void TextGameController::saveGame(const QString& path) {

}

void TextGameController::save() {

}

QString TextGameController::title() {
  return QString(master->title.c_str());
}

QString TextGameController::sceneText() {
    return QString(master->scene_text.c_str());
}

QString TextGameController::sceneTitle() {
    return QString(master->scene_title.c_str());
}

QString TextGameController::author() {
    return QString(master->author.c_str());
}

QString TextGameController::releaseDate() {
    return QString(master->date.c_str());
}

QString TextGameController::version() {
    return QString(master->version.c_str());
}

QString TextGameController::previousSceneText() {
  return QString(master->previous_scene_text.c_str());
}

QStringList TextGameController::choices() {
    QStringList qsl;

    for (auto& a : master->choices) {
      qsl << QString(a.c_str());
    }

    return qsl;
}

int TextGameController::sceneCount() {
    return master->scene_counter;
}

QString TextGameController::convertToHtml(const QString& str) {
  mk::MarkdownToHtml mdth;
  return QString(mdth.convertToHtml(str.toStdString()).c_str());
}

//QString convertToHtml(const QString& str) {

//}
