#ifndef SETTINGSCENES_H
#define SETTINGSCENES_H

#include <QWidget>

namespace Ui {
class SettingScenes;
}

class SettingScenes : public QWidget
{
    Q_OBJECT

public:
    explicit SettingScenes(QWidget *parent = nullptr);
    ~SettingScenes();
signals:
    void playWithAI();
    void playWithMan();

private:
    Ui::SettingScenes *ui;
};

#endif // SETTINGSCENES_H
