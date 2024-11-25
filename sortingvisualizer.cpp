
// sortingvisualizer.cpp
#include "sortingvisualizer.h"
#include <algorithm>
#include <QDebug>
#include <iostream>

SortingVisualizer::SortingVisualizer(QObject *parent)
    : QObject(parent)
    , sorting(false)
    , currentAlgorithm(Algorithm::BUBBLE_SORT)
    , currentIndex(0)
    , compareIndex(0)
    , swaps(0)
    , comparisons(0)
{
    // Create chart
    chart = new QChart();
    series = new QBarSeries();
    arraySize = 10;
    // Configure series
    if (arraySize <= 10) {
        series->setBarWidth(0.8);
    } else if (arraySize <= 100) {
        series->setBarWidth(0.9);
    } else {
        series->setBarWidth(1.0);
    }
    series->setLabelsVisible(false);

    // Set up axes
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, arraySize + 1);
    chart->addAxis(axisY, Qt::AlignLeft);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QStringList categories;
    for (int i = 0; i < arraySize; ++i) {
        categories << QString::number(i);
    }
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);

    // Add series to chart
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Configure chart appearance
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->legend()->hide();
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::transparent));
    chart->setTitle("Sorting Visualization");

    // Initialize data
    initializeArray();
}
void SortingVisualizer::setArraySize(int size) {
    arraySize = size;

    // Update x-axis categories
    QStringList categories;
    for (int i = 0; i < size; ++i) {
        categories << QString::number(i);
    }
    static_cast<QBarCategoryAxis*>(chart->axes(Qt::Horizontal).first())->setCategories(categories);

    // Update y-axis range
    static_cast<QValueAxis*>(chart->axes(Qt::Vertical).first())->setRange(0, size + 1);

    // Adjust bar width based on size
    if (size <= 10) {
        series->setBarWidth(0.8);
    } else if (size <= 100) {
        series->setBarWidth(0.9);
    } else {
        series->setBarWidth(1.0);
    }

    // Generate new array and update chart
    initializeArray();
}

int SortingVisualizer::getArraySize(){
    return arraySize;
}

void SortingVisualizer::initializeArray() {
    array.clear();
    // Generate random array
    for (int i = 0; i < arraySize; ++i) {
        array.push_back(i);
    }

    // Shuffle array
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(array.begin(), array.end(), gen);

    originalArray = array;
    updateChart();
}
void SortingVisualizer::updateChart()
{
    series->clear();
    QBarSet *normalSet = new QBarSet("");
    QBarSet *highlightedSet = new QBarSet("");

    for (int k = 0; k < array.size(); ++k) {
        *normalSet << array[k];
        *highlightedSet << 0;
    }

    normalSet->setColor(Qt::blue);
    highlightedSet->setColor(Qt::red);

    series->append(normalSet);
    series->append(highlightedSet);
    if (arraySize <= 10) {
        series->setBarWidth(0.8);
    } else if (arraySize <= 100) {
        series->setBarWidth(0.9);
    } else {
        series->setBarWidth(1.0);
    }
    chart->update();
}


void SortingVisualizer::highlightBars(int i, int j)
{
    // Clear existing series
    series->clear();

    // Create separate sets for normal and highlighted bars
    QBarSet *normalSet = new QBarSet("Normal");
    QBarSet *highlightedSet = new QBarSet("Highlighted");

    // Fill the sets
    for (int k = 0; k < array.size(); ++k) {
        if (k == i || k == j) {
            *normalSet << 0;  // Empty bar in normal set
            *highlightedSet << array[k];  // Value in highlighted set
        } else {
            *normalSet << array[k];  // Value in normal set
            *highlightedSet << 0;  // Empty bar in highlighted set
        }
    }

    // Set colors
    normalSet->setColor(Qt::blue);
    highlightedSet->setColor(Qt::red);

    // Add both sets to the series
    series->append(normalSet);
    series->append(highlightedSet);

    // Ensure bars are stacked
    if (arraySize <= 10) {
        series->setBarWidth(0.8);
    } else if (arraySize <= 100) {
        series->setBarWidth(0.9);
    } else {
        series->setBarWidth(1.0);
    }
    // Force chart update
    chart->update();
}

void SortingVisualizer::pauseSorting()
{
    sorting = false;
}
void SortingVisualizer::reset()
{
    sorting = false;
    currentIndex = 0;
    compareIndex = 0;
    comparisons = 0;
    swaps = 0;
    array = originalArray;
    partitionStack.clear();
    tempArray.clear();

    // Reset merge sort variables
    mergeSize = 0;
    mergeLeft = 0;
    currentLeft = 0;
    currentMid = 0;
    currentRight = 0;
    i = 0;
    j = 0;
    k = 0;

    shellGap = array.size() / 2;
    shellI = shellGap;
    shellJ = shellI;
    updateChart();
}
void SortingVisualizer::setAlgorithm(Algorithm alg)
{
    currentAlgorithm = alg;
    // Reset indices when changing algorithm
    currentIndex = 0;
    compareIndex = 0;
}

bool SortingVisualizer::performSortingStep()
{
    qDebug() << "performSortingStep";
    if (!sorting) return false;

    elapsedTime = algorithmTimer.elapsed(); // Update time every step

    bool result = false;
    switch (currentAlgorithm) {
    case Algorithm::BUBBLE_SORT:
        result = bubbleSortStep();
        break;
    case Algorithm::SELECTION_SORT:
        result = selectionSortStep();
        break;
    case Algorithm::INSERTION_SORT:
        result = insertionSortStep();
        break;
    case Algorithm::QUICK_SORT:
        result = quickSortStep();
        break;
    case Algorithm::MERGE_SORT:
        result = mergeSortStep();
        break;
    case Algorithm::SHELL_SORT:
        result = shellSortStep();
        break;
    case Algorithm::LINEAR_SEARCH:
        result = linearSearchStep();
        break;
    case Algorithm::BINARY_SEARCH:
        result = binarySearchStep();
        break;
    default:
        result = false;
        break;
    }
    return result;
}
// In sortingvisualizer.cpp, update these methods:

bool SortingVisualizer::bubbleSortStep()
{
    if (currentIndex >= array.size() - 1) {
        currentIndex = 0;
        compareIndex = 0;
        return false;
    }

    if (compareIndex < array.size() - currentIndex - 1) {
        comparisons++;
        if (array[compareIndex] > array[compareIndex + 1]) {
            std::swap(array[compareIndex], array[compareIndex + 1]);
            swaps++;
        }
        highlightBars(compareIndex, compareIndex + 1);
        compareIndex++;
        return true;
    }

    currentIndex++;
    compareIndex = 0;
    return true;
}

bool SortingVisualizer::selectionSortStep()
{
    if (currentIndex >= array.size() - 1) {
        return false;
    }

    if (compareIndex < array.size()) {
        comparisons++;
        if (array[compareIndex] < array[currentIndex]) {
            std::swap(array[compareIndex], array[currentIndex]);
            swaps++;
        }
        highlightBars(currentIndex, compareIndex);
        compareIndex++;
        return true;
    }

    currentIndex++;
    compareIndex = currentIndex + 1;
    return true;
}

bool SortingVisualizer::insertionSortStep()
{
    if (currentIndex >= array.size()) {
        return false;
    }

    if (compareIndex > 0) {
        comparisons++;
        if (array[compareIndex - 1] > array[compareIndex]) {
            std::swap(array[compareIndex - 1], array[compareIndex]);
            swaps++;
            compareIndex--;
            highlightBars(compareIndex, compareIndex + 1);
            return true;
        }
    }

    currentIndex++;
    compareIndex = currentIndex;
    return true;
}


// State variables for QuickSort
std::vector<std::pair<int, int>> partitionStack;  // Add this as a member variable in the header
int pivotIndex = 0;  // Add this as a member variable in the header
bool SortingVisualizer::quickSortStep() {
    // Initialize on first call
    if (partitionStack.empty() && currentIndex == 0) {
        partitionStack.push_back({0, static_cast<int>(array.size() - 1)});
        pivotIndex = array.size() - 1;
        currentIndex = 0;
        compareIndex = 0;
        return true;
    }

    // Check if sorting is complete
    if (partitionStack.empty()) {
        return false;
    }

    auto [left, right] = partitionStack.back();

    // If partition size is 1 or less, pop and continue
    if (left >= right) {
        partitionStack.pop_back();
        if (!partitionStack.empty()) {
            auto next = partitionStack.back();
            currentIndex = next.first;
            compareIndex = next.first;
            pivotIndex = next.second;
        }
        return !partitionStack.empty();
    }

    // Partition the array
    if (currentIndex < right) {
        comparisons++;
        if (array[currentIndex] < array[pivotIndex]) {
            std::swap(array[currentIndex], array[compareIndex]);
            swaps++;
            compareIndex++;
        }
        highlightBars(currentIndex, pivotIndex);
        currentIndex++;
        return true;
    }

    // Finalize partition
    std::swap(array[compareIndex], array[pivotIndex]);
    swaps++;

    int partition = compareIndex;
    partitionStack.pop_back();

    // Push sub-partitions
    if (partition + 1 < right) {
        partitionStack.push_back({partition + 1, right});
    }
    if (left < partition - 1) {
        partitionStack.push_back({left, partition - 1});
    }

    // Set up for next partition
    if (!partitionStack.empty()) {
        auto next = partitionStack.back();
        currentIndex = next.first;
        compareIndex = next.first;
        pivotIndex = next.second;
    }

    return !partitionStack.empty();
}


bool SortingVisualizer::mergeSortStep() {
    qDebug() << "mergeSortStep:";
    qDebug() << "  mergeSize:" << mergeSize;
    qDebug() << "  currentLeft:" << currentLeft;
    qDebug() << "  currentMid:" << currentMid;
    qDebug() << "  currentRight:" << currentRight;
    qDebug() << "  i:" << i << "j:" << j << "k:" << k;
    qDebug() << "  mergeLeft:" << mergeLeft;

    if (mergeSize == 0) {
        qDebug() << "  Initializing merge sort";
        tempArray = array;
        mergeSize = 1;
        mergeLeft = 0;
        currentLeft = 0;
        currentMid = 0;
        currentRight = 0;
        i = 0; j = 0; k = 0;
    }

    // Check if sorting is complete
    if (mergeSize >= array.size() && k >= currentRight) {
        qDebug() << "  Sorting complete";
        return false;
    }

    if (k >= currentRight) {
        qDebug() << "  Starting new merge segment";
        currentLeft = mergeLeft;
        currentMid = std::min(currentLeft + mergeSize, static_cast<int>(array.size()));
        currentRight = std::min(currentLeft + 2 * mergeSize, static_cast<int>(array.size()));
        i = currentLeft;
        j = currentMid;
        k = currentLeft;
        mergeLeft += 2 * mergeSize;

        if (mergeLeft >= array.size()) {
            qDebug() << "  Completing merge pass, doubling mergeSize";
            tempArray = array;
            mergeLeft = 0;
            mergeSize *= 2;
        }

        highlightBars(currentLeft, currentRight - 1);
        return true;
    }

    qDebug() << "  Merging elements";
    if (i < currentMid && (j >= currentRight || tempArray[i] <= tempArray[j])) {
        array[k] = tempArray[i];
        highlightBars(k, i);
        i++;
        comparisons++;
        swaps++;
    } else if (j < currentRight) {
        array[k] = tempArray[j];
        highlightBars(k, j);
        j++;
        comparisons++;
        swaps++;
    }
    k++;
    updateChart();
    return true;
}

int SortingVisualizer::getComparisons() const { return comparisons; }
int SortingVisualizer::getSwaps() const { return swaps; }

bool SortingVisualizer::shellSortStep() {
    if (shellGap == 0) {
        return false;
    }

    if (shellI < array.size()) {
        if (shellJ >= shellGap && array[shellJ - shellGap] > array[shellJ]) {
            std::swap(array[shellJ - shellGap], array[shellJ]);
            highlightBars(shellJ - shellGap, shellJ);
            shellJ -= shellGap;
            comparisons++;
            swaps++;
        } else {
            shellI++;
            shellJ = shellI;
        }
        updateChart();
        return true;
    } else {
        shellGap /= 2;
        shellI = shellGap;
        shellJ = shellI;
        updateChart();
        return true;
    }
}

bool SortingVisualizer::linearSearchStep() {
    if (currentIndex >= array.size()) {
        searchFound = false;
        return false;
    }

    comparisons++;
    highlightBars(currentIndex, -1);

    if (array[currentIndex] == searchTarget) {
        searchFound = true;
        searchResult = currentIndex;
        return false;
    }

    currentIndex++;
    return true;
}
bool SortingVisualizer::binarySearchStep() {
    // Initialize the search range on first step
    if (currentIndex == 0 && compareIndex == 0) {
        currentIndex = 0;                    // left boundary
        compareIndex = array.size() - 1;     // right boundary
        return true;
    }

    // Make sure we haven't crossed boundaries
    if (currentIndex > compareIndex) {
        searchFound = false;
        searchResult = -1;
        return false;
    }

    // Calculate middle point
    int mid = currentIndex + (compareIndex - currentIndex) / 2;

    // Highlight current element being compared and increment counter
    highlightBars(mid, -1);
    comparisons++;

    // Found the target
    std::cout << "array[mid]: " << std::to_string(array[mid])  + " searchTarget: " << std::to_string(searchTarget) << std::endl;
    if (array[mid] == searchTarget) {
        searchFound = true;
        searchResult = mid;
        return false;
    }

    // Adjust search range
    if (array[mid] > searchTarget) {
        compareIndex = mid - 1;  // Search in left half
    } else {
        currentIndex = mid + 1;  // Search in right half
    }

    // If we've narrowed down to a single element and it's not the target
    if (currentIndex == compareIndex) {
        if (array[currentIndex] != searchTarget) {
            searchFound = false;
            searchResult = -1;
            return false;
        }
    }

    return true;
}

void SortingVisualizer::startSorting() {
    sorting = true;
    currentIndex = 0;
    compareIndex = 0;

    // Reset statistics
    comparisons = 0;
    swaps = 0;
    searchFound = false;
    searchResult = -1;

    // For binary search, ensure array is sorted
    if (currentAlgorithm == Algorithm::BINARY_SEARCH) {
        std::sort(array.begin(), array.end());
        updateChart();
    }

    algorithmTimer.start();
}
