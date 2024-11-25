// sortingvisualizer.h
#ifndef SORTINGVISUALIZER_H
#define SORTINGVISUALIZER_H

#include <QObject>
#include <QtCharts>
#include <vector>
#include <random>

class SortingVisualizer : public QObject
{
    Q_OBJECT

public:
    enum class Algorithm {
        BUBBLE_SORT,
        SELECTION_SORT,
        INSERTION_SORT,
        QUICK_SORT,
        MERGE_SORT,
        SHELL_SORT,
        LINEAR_SEARCH,
        BINARY_SEARCH
    };

    explicit SortingVisualizer(QObject *parent = nullptr);

    QChart* getChart() const { return chart; }
    bool isSorting() const { return sorting; }
    void setSorting(bool sorting){ this->sorting = sorting;}
    void startSorting();
    void pauseSorting();
    void reset();
    bool performSortingStep();
    void setAlgorithm(Algorithm alg);
    int getComparisons() const;
    int getSwaps() const;
    qint64 getElapsedTime() const { return elapsedTime; }
    void setArraySize(int size);
    int getArraySize();
    Algorithm getCurrentAlgorithm() const { return currentAlgorithm; }
    void setSearchTarget(int target) { searchTarget = target; }
    bool wasSearchSuccessful() const { return searchFound; }
    int getSearchResult() const { return searchResult; }


private:
    void initializeArray();
    void updateChart();
    void highlightBars(int i, int j);

    // Sorting algorithms
    bool bubbleSortStep();
    bool selectionSortStep();
    bool insertionSortStep();
    bool quickSortStep();
    bool mergeSortStep();

    std::vector<int> array;
    std::vector<int> originalArray;
    QChart *chart;
    QBarSeries *series;  // Changed to QVBarSeries
    bool sorting;
    Algorithm currentAlgorithm;

    // Sorting state variables
    int currentIndex;
    int compareIndex;
    int comparisons;
    int swaps;

    // For QuickSort
    std::vector<std::pair<int, int>> partitionStack;
    int pivotIndex;

    // For MergeSort
    std::vector<int> tempArray;
    int mergeLeft;
    int mergeRight;
    int mergeMiddle;
    int mergeSize;  // Track current merge size

    int currentLeft = 0;
    int currentMid = 0;
    int currentRight = 0;
    int i = 0, j = 0, k = 0;

    bool shellSortStep();
    QElapsedTimer algorithmTimer;
    qint64 elapsedTime;  // in milliseconds

    int shellGap;
    int shellI;
    int shellJ;

    int arraySize;
    int searchTarget;
    int searchResult;
    bool searchFound;
    bool linearSearchStep();
    bool binarySearchStep();

};

#endif // SORTINGVISUALIZER_H
