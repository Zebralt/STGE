#ifndef TEXTGAME_CONTROLLER_H
#define TEXTGAME_CONTROLLER_H

#include <QObject>

class TextGame;

/// INTERFACE BETWEEN MODEL AND Qt (yeah, MVC ...)

class TextGameController : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString title READ title)
  Q_PROPERTY(QString author READ author)
  Q_PROPERTY(QString date READ releaseDate)
  Q_PROPERTY(QString version READ version)
  Q_PROPERTY(QString scene_title READ sceneTitle NOTIFY sceneTitleChanged)
  Q_PROPERTY(QString scene READ sceneText NOTIFY sceneChanged)
  Q_PROPERTY(QString previous_scene READ previousSceneText NOTIFY previousSceneChanged)
  Q_PROPERTY(QStringList choices READ choices NOTIFY choicesChanged)
  Q_PROPERTY(int count READ sceneCount)

public:
  TextGameController(QObject* p = 0);

  ///
  /// EXPOSED FUNCTIONS
  ///

  Q_INVOKABLE void loadSavedGame(const QString& path);
  Q_INVOKABLE void saveGame(const QString& path);
  Q_INVOKABLE void save();
  Q_INVOKABLE void proceed(const QString& choice);
  Q_INVOKABLE void initialize();

  QString title();
  QString sceneText();
  QString sceneTitle();
  QString author();
  QString releaseDate();
  QString version();
  QString previousSceneText();
  QStringList choices();
  int sceneCount();

signals:
  void sceneChanged();
  void previousSceneChanged();
  void sceneTitleChanged();
  void choicesChanged();

private:
  TextGame* master = nullptr;
};


#endif // TEXTGAME_CONTROLLER_H
