// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "sortingvisualizer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_resetButton_clicked();
    void on_speedSlider_valueChanged(int value);
    void on_algorithmComboBox_currentIndexChanged(int index);
    void updateChart();
    void on_sizeComboBox_currentIndexChanged(int index);  // Add this line
    void on_statsButton_clicked();
    void on_findEdit_textChanged(const QString &text);


private:
    Ui::MainWindow *ui;
    SortingVisualizer *visualizer;
    QTimer *timer;
    int delay;
    void showStatsDialog();
    struct AlgorithmStats {
        QString name;
        qint64 time;
        int comparisons;
        int swaps;
        int dataSize;
    };
    QVector<AlgorithmStats> completedAlgorithms;
    int searchTarget;
    bool searchTargetValid;
};

#endif // MAINWINDOW_H
