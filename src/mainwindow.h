#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAggiungi_clicked();
    void aggiornaTotale();
    void mostraMenuContextuale(const QPoint &pos);
    void aggiornaStileOggetto(QListWidgetItem* item);
    void filtraPerCategoria(const QString &categoriaSelezionata);

private:
    void inizializzaCategorie();  // Spostato in private

    Ui::MainWindow *ui;
};

#endif