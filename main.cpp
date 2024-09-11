// main.cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "data_structures.h"


// Global variables to keep track of the most recent source and destination vertices
int recentSource = -1;
int recentDestination = -1;
int singlepair = 0;
int singlesource = 0;

void handleInstructions(const std::vector<std::string>& instructions, const std::string &filename, const std::string &graphType, int flag)
{
    std::vector<Vertex *> V;
    std::vector<std::vector<Node *>> ADJ;
    int numVertices, numEdges;

    // Build the graph
    buildGraph(filename, V, ADJ, numVertices, numEdges, flag, graphType);

    // Loop to handle instructions
    for (const std::string& instruction : instructions) {
        std::istringstream iss(instruction);
        std::vector<std::string> inst;
        std::string word;
        while (iss >> word)
        {
            inst.push_back(word);
        }

        if (inst.empty())
        {
            continue; // Empty line
        }

        if (inst[0] == "Stop")
        {
            break;
        }
        else if (inst[0] == "PrintADJ")
        {
            // Print the adjacency lists
            printADJ(ADJ);
        }
        else if (inst[0] == "SinglePair")
        {
            if (inst.size() != 3)
            {
                std::cerr << "Invalid number of arguments for SinglePair instruction." << std::endl;
                continue;
            }
            int source = std::stoi(inst[1]);
            int destination = std::stoi(inst[2]);
            dijkstraSinglePair(ADJ, V, source, destination);
            // Update the most recent source and destination vertices
            recentSource = source;
            recentDestination = destination;
            singlepair = 1;
        }
        else if (inst[0] == "SingleSource")
        {
            if (inst.size() != 2)
            {
                std::cerr << "Invalid number of arguments for SingleSource instruction." << std::endl;
                continue;
            }
            int source = std::stoi(inst[1]);
            dijkstra(V, ADJ, source);
            // Update the most recent source and destination vertices
            recentSource = source;
            recentDestination = -1; // Reset the destination
            singlesource = 1;
        }
        else if (inst[0] == "PrintLength")
        {
            if (inst.size() != 3)
            {
                std::cerr << "Invalid number of arguments for PrintLength instruction." << std::endl;
                continue;
            }

            int s = std::stoi(inst[1]);
            int t = std::stoi(inst[2]);
            if (singlepair == 1 && s == recentSource && t == recentDestination)
            {
                printLength(V, s, t);
            }
            else if (singlesource == 1 && s == recentSource)
            {
                printLength(V, s, t);
            }
            else
            {
                std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
            }
        }
        else if (inst[0] == "PrintPath")
        {
            if (inst.size() != 3)
            {
                std::cerr << "Invalid number of arguments for PrintPath instruction." << std::endl;
                continue;
            }
            int s = std::stoi(inst[1]);
            int t = std::stoi(inst[2]);
            if (singlepair == 1 && s == recentSource && t == recentDestination)
            {
                printPath(V, s, t);
            }
            else if (singlesource == 1 && s == recentSource)
            {
                printPath(V, s, t);
            }
            
        }
        else
        {
            std::cerr << "Invalid instruction: " << inst[0] << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <graphType> <source>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string graphType = argv[2];
    int flag = std::stoi(argv[3]);
    if (flag != 1 && flag != 2) {
        return 1;
    }

    // Read all instructions into an array
    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "Stop") {
            instructions.push_back(line);
            break;
        }
        instructions.push_back(line);
    }

    // Optimizing instructions
    std::vector<std::string> optimizedInstructions;
    for (size_t i = 0; i < instructions.size(); ++i) {
        // Check if the first word of the instruction is "SingleSource" or "SinglePair"
        std::istringstream iss(instructions[i]);
        std::string firstWord;
        iss >> firstWord;
        if ((firstWord == "SingleSource" || firstWord == "SinglePair") &&
            ((i + 1 < instructions.size() && (instructions[i + 1].find("SingleSource") == 0 || instructions[i + 1].find("SinglePair") == 0)) ||
             i + 1 == instructions.size())) {
            continue;
        }
        // Otherwise, add the current instruction to the optimized set of instructions
        optimizedInstructions.push_back(instructions[ i]);
    }

    // Process optimized instructions
    handleInstructions(optimizedInstructions, filename, graphType, flag);

    return 0;
}
