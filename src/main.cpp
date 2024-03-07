#include <iostream>
#include <vector>
#include <linked_list.hpp> 
#include <graph.hpp> 
#include <string>
#include <map>
#include <fstream>
#include <search.hpp>
#include <bst.hpp>

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

bool testBST() {
    BST<int> bst;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Insert " << i << " into BST" << std::endl;
        bst.insert(i);
        
        std::cout << "Find " << i << ". ";  
        if (bst.find(i) != NULL && bst.find(i)->key == i)
            std::cout << "Found " << i << " in BST" << std::endl;
        else
            return false;
        
        std::cout << "Find " << i+1 << ". ";  
        if (bst.find(i+1) == NULL)
            std::cout << "Not found " << i+1 << " in BST" << std::endl;
        else
            return false;

        std::cout << std::endl;
    }

    std::cout << "Maximum value in BST: ";
    if (bst.findMaximum() == NULL || bst.findMaximum()->key != 9)
        return false;
    else
        std::cout << bst.findMaximum()->key << std::endl << std::endl;
    
    
    for (int i = 0; i < 9; ++i) {
        std::cout << "Remove " << i << " out of BST" << std::endl;
        bst.remove(i);

        std::cout << "Find " << i << ". ";  
        if (bst.find(i) == NULL) 
            std::cout << "Not found " << i << " in BST" << std::endl;
        else
            return false;

        std::cout << "Find " << i+1 << ". ";  
        if (bst.find(i+1) != NULL && bst.find(i+1)->key == i+1)
            std::cout << "Found " << i+1 << " in BST" << std::endl;
        else
            return false;
        std::cout << std::endl;
    }

    return true;
}


bool testGraph() {
    Graph G(6);
    G.insertEdge(0, 1, 1);
    G.insertEdge(1, 2, 2);
    G.insertEdge(1, 3, 3);
    G.insertEdge(2, 4, 4);
    G.insertEdge(4, 3, 5);
    G.insertEdge(4, 5, 6);


    std::cout << "Shortest path from 0 to 5 by " << ": " ;
    std::vector<int> path = G.search(0, 5, bfs);
    for (int i = 0; i < path.size(); ++i) 
        std::cout << path[i] << " ";
    std::cout << "\n";
    std::cout << "Total Distance: " << G.distance(5) << std::endl;
    
    return true;
}

void searchOnCampus(std::string start = "BELL", std::string destination = "HAPG") {
    std::ifstream reader("assets/map_info.txt");
    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<int> xs;
    std::vector<int> ys;
    for (int i = 0; i < n; ++i) {
        int index, x, y;
        std::string name;
        reader >> index >> name >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
        name2index[name] = index;
        index2name[index] = name;
    }

    Graph G(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        reader >> u >> v;
        int dx = xs[u] - xs[v];
        int dy = ys[u] - ys[v];
        int w = dx * dx + dy * dy;
        G.insertEdge(u, v, w);
    }

    std::vector<int> path = G.search(name2index[start], name2index[destination], bfs);

    std::cout << "Shorest path from " << start  << " to " << " detination: " << start ;
    for (int i = 1; i < path.size(); ++i)
        std::cout << " -> " << index2name[path[i]];
    
    std::cout << "\n";
    
    std::cout << "Total Distance: " << G.distance(name2index[destination]) << std::endl;

#ifdef OPENCV
    cv::Mat image = cv::imread("assets/map.png");
    for (int i = 0; i < n; ++i) {
        cv::circle(image, cv::Point(xs[i], ys[i]), 10, cv::Scalar(255, 0, 0), -1);
        cv::putText(image, index2name[i],  cv::Point(xs[i], ys[i]-10),  cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 0), 1);
    }

    for (int i = 0; i < path.size(); ++i) {
        if (i > 0) 
            cv::line(image, cv::Point(xs[path[i]], ys[path[i]]), cv::Point(xs[path[i-1]], ys[path[i-1]]), cv::Scalar(255, 0, 0), 4);
    }
    //cv::resize(image, image, cv::Size(), 0.75, 0.75);
    cv::imshow("Shorest path from " + start + " to " + destination, image);
    cv::waitKey(0);

#else
    std::cout << "You have to use OpenCV to visualize your map road\n";
#endif


}
int main(int argc, char **args) {
    
    std::cout << "Perform unit test on your BST implementation" << std::endl;
    if (testBST())
        std::cout << "Your BST implementation is correct" << std::endl;
    else {
        std::cout << "Your BST implementation is incorrect" << std::endl;
        return -1;
    }

    std::cout << std::endl << "Perform unit test on your implementation with graph" << std::endl;
    testGraph();
    

    std::cout << "\n\n";
    
    searchOnCampus("JBHT", "HAPG");

    std::cout << "\n";
    
}
