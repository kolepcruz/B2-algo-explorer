#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QtCharts>
#include <QChartView>
#include <QDebug>


// Implementation:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , delay(1)
{
    ui->setupUi(this);

    // Create the visualizer
    visualizer = new SortingVisualizer(this);
    timer = new QTimer(this);

    // Create chart view
    QChartView *chartView = new QChartView(visualizer->getChart(), this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setMinimumHeight(400);

    // Add chart to the main layout
    ui->centralwidget->layout()->addWidget(chartView);

    // Connect timer to update function
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChart);

    // Initialize the chart with data
    visualizer->reset();
    qDebug() << "MainWindow initialized";
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    qDebug() << "on_startButton_clicked";
    if (!visualizer->isSorting()) {
        visualizer->reset(); // Added reset call

        if (visualizer->getCurrentAlgorithm() >= SortingVisualizer::Algorithm::LINEAR_SEARCH) {
            if (!searchTargetValid) {
                return;
            }
            visualizer->setSearchTarget(searchTarget);
        }
        visualizer->startSorting();
        timer->start(delay);
        ui->startButton->setText("Pause");
    } else {
        visualizer->pauseSorting();
        timer->stop();
        ui->startButton->setText("Start");
    }
}

void MainWindow::on_resetButton_clicked()
{
    qDebug() << "on_resetButton_clicked";
    timer->stop();
    visualizer->reset();
    ui->startButton->setText("Start");
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    qDebug() << "on_speedSlider_valueChanged";
    delay = std::max(1, 100 - value);  // Ensure delay is at least 1ms
    char speedLabelText[255];
    sprintf(speedLabelText,"delay ms: %d",delay);
    ui->speedLabel->setText(QString(speedLabelText));

    if (timer->isActive()) {
        timer->setInterval(delay);
    }
}

void MainWindow::on_algorithmComboBox_currentIndexChanged(int index) {
    qDebug() << "Algorithm changed to:" << index;

    // Show/hide search input based on algorithm type
    bool isSearchAlgorithm = index >= static_cast<int>(SortingVisualizer::Algorithm::LINEAR_SEARCH);
    ui->findEdit->setVisible(isSearchAlgorithm);

    // Enable/disable start button based on search validity
    if (isSearchAlgorithm) {
        ui->startButton->setEnabled(searchTargetValid);
    } else {
        ui->startButton->setEnabled(true);
    }

    visualizer->setAlgorithm(static_cast<SortingVisualizer::Algorithm>(index));
}
void MainWindow::updateChart() {
    if (!visualizer->isSorting()) return;

    // Update runtime in real-time
    qint64 elapsed = visualizer->getElapsedTime();
    int hours = elapsed / (1000 * 60 * 60);
    int minutes = (elapsed % (1000 * 60 * 60)) / (1000 * 60);
    int seconds = (elapsed % (1000 * 60)) / 1000;
    int milliseconds = elapsed % 1000;

    QString timeStr = QString("%1:%2:%3:%4")
                          .arg(hours, 2, 10, QChar('0'))
                          .arg(minutes, 2, 10, QChar('0'))
                          .arg(seconds, 2, 10, QChar('0'))
                          .arg(milliseconds, 3, 10, QChar('0'));
    ui->timeLabel->setText(timeStr);

    if (!visualizer->performSortingStep()) {
        timer->stop();
        AlgorithmStats stats;
        stats.name = ui->algorithmComboBox->currentText();
        stats.time = visualizer->getElapsedTime();
        stats.comparisons = visualizer->getComparisons();
        stats.swaps = visualizer->getSwaps();
        stats.dataSize = visualizer->getArraySize();

        auto it = std::find_if(completedAlgorithms.begin(), completedAlgorithms.end(),
                               [&](const AlgorithmStats& s) {
                                   return s.name == stats.name && s.dataSize == stats.dataSize;
                               });

        if (it != completedAlgorithms.end()) {
            *it = stats;
        } else {
            completedAlgorithms.append(stats);
        }
        ui->startButton->setText("Start");
        visualizer->setSorting(false);
    }

    QString statsText = QString("Comparisons: %1\nSwaps: %2")
                            .arg(visualizer->getComparisons())
                            .arg(visualizer->getSwaps());
    ui->statsLabel->setText(statsText);
}

void MainWindow::on_sizeComboBox_currentIndexChanged(int index)
{
    qDebug() << "Size changed to:" << index;
    int size;
    switch(index) {
    case 0:
        size = 10;
        break;
    case 1:
        size = 100;
        break;
    case 2:
        size = 1000;
        break;
    default:
        size = 100;
    }
    visualizer->setArraySize(size);
}

void MainWindow::showStatsDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Algorithm Performance Comparison");
    dialog.resize(1000, 800);

    // Generate distinct colors for algorithms
    QVector<QColor> algorithmColors;
    const int hueStep = 360 / 8; // 8 different algorithms
    for (int i = 0; i < 8; ++i) {
        algorithmColors.append(QColor::fromHsv(i * hueStep, 200, 230));
    }

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QMap<int, QVector<AlgorithmStats>> statsBySize;
    for (const auto &stat : completedAlgorithms) {
        statsBySize[stat.dataSize].append(stat);
    }

    QTabWidget *tabWidget = new QTabWidget(&dialog);
    layout->addWidget(tabWidget);

    for (auto it = statsBySize.begin(); it != statsBySize.end(); ++it) {
        QWidget *tabPage = new QWidget();
        QVBoxLayout *tabLayout = new QVBoxLayout(tabPage);

        QStringList categories;
        QVector<QBarSet*> timeSets;
        QVector<QBarSet*> compSets;
        QVector<QBarSet*> swapSets;

        for (int i = 0; i < it.value().size(); ++i) {
            const auto &stat = it.value()[i];
            categories << stat.name;

            QBarSet *timeSet = new QBarSet(stat.name);
            QBarSet *compSet = new QBarSet(stat.name);
            QBarSet *swapSet = new QBarSet(stat.name);

            *timeSet << stat.time;
            *compSet << stat.comparisons;
            *swapSet << stat.swaps;

            timeSet->setColor(algorithmColors[i]);
            compSet->setColor(algorithmColors[i]);
            swapSet->setColor(algorithmColors[i]);

            timeSets.append(timeSet);
            compSets.append(compSet);
            swapSets.append(swapSet);
        }

        auto createChart = [&](const QString &title, const QVector<QBarSet*> &sets) {
            QChart *chart = new QChart();
            QBarSeries *series = new QBarSeries();
            series->setBarWidth(1.0);
            series->setLabelsPosition(QAbstractBarSeries::LabelsCenter);
            for (auto set : sets) {
                series->append(set);
            }
            chart->addSeries(series);
            chart->setTitle(title);
            QValueAxis *axisY = new QValueAxis();
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setMinimumHeight(200);
            tabLayout->addWidget(chartView);
        };

        createChart("Execution Time (ms)", timeSets);
        createChart("Number of Comparisons", compSets);
        createChart("Number of Swaps", swapSets);

        tabWidget->addTab(tabPage, QString("%1 Elements").arg(it.key()));
    }

    dialog.exec();
}
void MainWindow::on_statsButton_clicked() {
    showStatsDialog();
}

void MainWindow::on_findEdit_textChanged(const QString &text) {
    bool ok;
    int value = text.toInt(&ok);
    searchTargetValid = ok && value > 0 && value <= visualizer->getArraySize();
    searchTarget = ok ? value : 0;
    // Update UI to reflect validity
    QPalette palette = ui->findEdit->palette();
    palette.setColor(QPalette::Text, searchTargetValid ? Qt::black : Qt::red);
    ui->findEdit->setPalette(palette);

    // Only enable start button for search algorithms if input is valid
    if (visualizer->getCurrentAlgorithm() >= SortingVisualizer::Algorithm::LINEAR_SEARCH) {
        ui->startButton->setEnabled(searchTargetValid);
    }
}
