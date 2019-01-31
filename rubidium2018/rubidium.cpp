#include <limits>
#include <array>
#include <memory>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

constexpr int PlusInf = numeric_limits<int>::max();

struct Point
{
    int x;
    int y;
};

struct cmpPoint
{
    bool operator()(const Point a,const Point b) const 
    {
        if ( a.x == b.x) return a.y < b.y;
        else return a.x < b.x;
    }
};
struct Square
{
    Point topRight;
    Point bottomLeft;
};

class QuadNode
{
public:
    enum Dir
    {
        NE = 0,
        SE,
        SW,
        NW,
        NONE
    };

    Point point;
    Square square;
    std::array<unique_ptr<QuadNode>, 4> children;
    QuadNode* parent;

    Dir getDir(Point newPoint);
    QuadNode* insertPoint(Point newPoint);
    Point findClosest(const Point p,unsigned int bestDistance, Point bestPoint,QuadNode*);
    static unsigned int getDistance(Point a, Point b);
      
private:
    unsigned int getSquareSize();
    Point getCenter();
    Square getNewSquare(Dir dir);
    unsigned int getDistanceToSquare(const Point p);
};


class QuadTree
{
public:
    QuadTree(Point point,int squareSize);
    void insertPoint(Point newPoint);
    Point findClosestPoint(Point p) noexcept;

private:
    QuadNode _root;
    
    std::map<Point,QuadNode*,cmpPoint> _nodeMap;
   
};

QuadNode::Dir QuadNode::getDir(Point newPoint)
{
    Dir result = NONE;
    Point center = getCenter();
   
    if (newPoint.x >= center.x && newPoint.y >= center.y)
    {
        result = NE;
    }
    else if (newPoint.x >= center.x && newPoint.y <= center.y)
    {
        result = SE;
    }
    else if (newPoint.x <= center.x && newPoint.y <= center.y)
    {
        result = SW;
    }
    else if (newPoint.x <= center.x && newPoint.y >= center.y)
    {
        result = NW;
    }
    return result;
}

QuadNode* QuadNode::insertPoint(Point newPoint)
{
    auto dir = getDir(newPoint);
    auto& newNode = children[dir];
    if (newNode)
    {
        return newNode->insertPoint(newPoint);
    }
    else
    {
        newNode.reset(new QuadNode());
        newNode->point = newPoint;
        newNode->square = getNewSquare(dir);
        newNode->parent = this;
    }
    return newNode.get();
}


unsigned int QuadNode::getDistance(Point a, Point b)
{
    unsigned xD = static_cast<unsigned>(abs(a.x - b.x));
    unsigned yD = static_cast<unsigned>(abs(a.y - b.y));
    unsigned d = std::max(xD / 2, yD / 2);
    return d;
}

unsigned QuadNode::getSquareSize()
{
    unsigned sqareSize = static_cast<unsigned>(square.topRight.x - square.bottomLeft.x);
    return sqareSize;
}

Point QuadNode::getCenter()
{
    int halfSquare = static_cast<int>(getSquareSize()) / 2;
    int cX = square.bottomLeft.x + halfSquare;
    int cY = square.bottomLeft.y + halfSquare;
    return { cX,cY };
}

Square QuadNode::getNewSquare(Dir dir)
{
    Square newSquare;
    Point center = getCenter();
    int newSize = static_cast<int>(std::ceil(getSquareSize() / 2.0));
    switch (dir)
    {
    case QuadNode::NE:
        newSquare.bottomLeft = center;
        newSquare.topRight = { center.x + newSize,center.y + newSize };
        break;
    case QuadNode::SE:
        newSquare.bottomLeft = { center.x,center.y - newSize };
        newSquare.topRight =   { center.x + newSize,center.y };
        break;
    case QuadNode::SW:
        newSquare.bottomLeft = { center.x - newSize ,center.y - newSize };
        newSquare.topRight = center;
        break;
    case QuadNode::NW:
        newSquare.bottomLeft = { center.x - newSize,center.y};
        newSquare.topRight = { center.x,center.y + newSize };
        break;
    case QuadNode::NONE:
        break;
    default:
        break;
    }
    return newSquare;
}

unsigned int QuadNode::getDistanceToSquare(const Point p)
{
    int dx = std::max(std::max(square.bottomLeft.x - p.x, 0), p.x - square.topRight.x);
    int dy = std::max(std::max(square.bottomLeft.y - p.y, 0), p.y - square.topRight.y);
    return   static_cast<unsigned>(abs(dx)) / 2 + static_cast<unsigned>(abs(dy)) / 2;
}

QuadTree::QuadTree(Point point, int squareSize)
{
    _root.point = point;
    _root.square.bottomLeft = { -squareSize,-squareSize };
    _root.square.topRight = { squareSize,squareSize };
    _root.parent = nullptr;
     _nodeMap[point] = &_root;
}

void QuadTree::insertPoint(Point newPoint)
{
     _nodeMap[newPoint] = _root.insertPoint(newPoint);
}

Point QuadTree::findClosestPoint(Point p)  noexcept
{
    auto closestPoint = _nodeMap[p]->findClosest(p, PlusInf, { PlusInf,PlusInf },nullptr);
    return closestPoint;
}

Point QuadNode::findClosest(const Point targetPoint, unsigned int bestDistance, Point bestPoint, QuadNode* from)
{
    Point minPoint = bestPoint;
    if (targetPoint.x != point.x || targetPoint.y != point.y)
    {
        unsigned int newDistance = QuadNode::getDistance(point, targetPoint);
        if (newDistance < bestDistance)
        {
            bestDistance = newDistance;
            minPoint = point;
        }
    }
    
    for (const auto& child : children)
    {
        if (child && child.get() != from)
        {
            auto distToSquare = child->getDistanceToSquare(targetPoint);
            if (distToSquare <= bestDistance)
            {
                auto bestChildPoint = child->findClosest(targetPoint,bestDistance,minPoint,this);
                unsigned int newDistance = QuadNode::getDistance(bestChildPoint, targetPoint);
                if (newDistance < bestDistance)
                {
                    bestDistance = newDistance;
                    minPoint = bestChildPoint;
                }
            }
        }
    } 
    if ( parent != nullptr && parent != from) 
    {
        minPoint = parent->findClosest(targetPoint,bestDistance,minPoint,this);
    }
    return minPoint;
}


unsigned solution(vector<int> &X, vector<int> &Y) 
{
    int maxX = *max_element(X.begin(), X.end());
    int maxY = *max_element(Y.begin(), Y.end());
    int minX = *min_element(X.begin(), X.end());
    int minY = *min_element(Y.begin(), Y.end());

    int squareSize = max({abs(maxX),abs(maxY),abs(minX),abs(minY)});
    QuadTree quadTree({X[0],Y[0]}, squareSize);
    for (unsigned int i = 1; i < X.size(); ++i)
    {
        Point point = { X[i],Y[i] };
        quadTree.insertPoint(point);
    }
    unsigned result = PlusInf;
    for (unsigned int i = 0; i < X.size(); ++i)
    {
        Point point = { X[i],Y[i] };
        Point closestPoint = quadTree.findClosestPoint(point);
        result = min(QuadNode::getDistance(point, closestPoint), result);
    }
    return result;
}

void test(string fileName)
{
    ifstream inFile(fileName);
    string str;
    getline(inFile, str);
    unsigned expected = static_cast<unsigned>(atoi(str.c_str()));
    vector<int> X;
    vector<int> Y;
    while (getline(inFile, str))
    {
        int x, y;
        istringstream iss(str);
        iss >> x >> y;
        X.push_back(x);
        Y.push_back(y);
    }
    auto result = solution(X, Y);

    if (result != expected)
    {
        cout << "Test " << fileName << " failed Ans: " << result << " expected " << expected << endl;
    }
}


int main()
{
    test("../test_cases/tc1.txt");
    test("../test_cases/tc2.txt");
    test("../test_cases/tc4.txt");
    return 0;
}


