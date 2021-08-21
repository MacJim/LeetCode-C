/*
 * 332. Reconstruct Itinerary
 * https://leetcode.com/problems/reconstruct-itinerary/
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Backtracking
// WRONG ANSWER because the same ticket may appear multiple times.
class Solution1 {
public:
    std::vector<std::string> findItinerary(const std::vector<std::vector<std::string>>& tickets) {
        auto ticketsMap = std::unordered_map<std::string, std::set<std::string>>();    // Use set to sort the destinations.
        for (const auto& ticket: tickets) {
            ticketsMap[ticket[0]].insert(ticket[1]);
        }

        int remainingTickets = tickets.size();
        auto returnValue = std::vector<std::string>({"JFK"});

        while (remainingTickets > 0) {
            auto currentNode = returnValue.back();

            auto& destinations = ticketsMap[currentNode];
            if (destinations.empty()) {
                // Dead end.
                while (true) {
                    returnValue.pop_back();
                    remainingTickets += 1;

                    auto previousNode = returnValue.back();
                    ticketsMap[previousNode].insert(currentNode);    // Restore this ticket.

                    auto nextNodeIt = ticketsMap[previousNode].find(currentNode);
                    nextNodeIt ++;
                    if (nextNodeIt != ticketsMap[previousNode].end()) {
                        // We have a next node.
                        returnValue.push_back(*nextNodeIt);
                        remainingTickets -= 1;
                        ticketsMap[previousNode].erase(nextNodeIt);

                        break;
                    }
                }
            } else {
                // Choose the smallest next node.
                returnValue.push_back(*(destinations.begin()));
                remainingTickets -= 1;
                destinations.erase(destinations.begin());
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Fixed 1
// Runtime: 16 ms, faster than 94.25% of C++ online submissions for Reconstruct Itinerary.
// Memory Usage: 13.8 MB, less than 98.32% of C++ online submissions for Reconstruct Itinerary.
class Solution {
public:
    std::vector<std::string> findItinerary(const std::vector<std::vector<std::string>>& tickets) {
        // Create tickets map.
        auto ticketsMap = std::unordered_map<std::string, std::vector<std::string>>();    // MARK: I should have used an `std::multiset` instead of a vector.
        for (const auto& ticket: tickets) {
            ticketsMap[ticket[0]].push_back(ticket[1]);
        }
        // This sorting process wouldn't be necessary if I were to use `std::multiset`.
        for (auto& [_, destinations]: ticketsMap) {
            std::sort(destinations.begin(), destinations.end());
        }

        // Count remaining tickets since there's no way to tell if there are any tickets remaining in `ticketsMap`.
        int remainingTickets = tickets.size();
        auto returnValue = std::vector<std::string>({"JFK"});

        while (remainingTickets > 0) {
            auto currentNode = returnValue.back();
            auto& destinations = ticketsMap[currentNode];

            // Find the smallest next node (if it exists).
            bool nextTicketFound = false;
            for (auto& destination: destinations) {
                if (destination.size() == 3) {
                    // This ticket is unused.
                    returnValue.push_back(destination);
                    destination.push_back(' ');    // Mark as visited by inserting a space at the end.

                    nextTicketFound = true;
                    break;
                }
            }

            if (nextTicketFound) {
                // Next node found. Go ahead.
                remainingTickets -= 1;
            } else {
                // Dead end. Go back.
                while (true) {
                    currentNode = returnValue.back();    // Remember to set `currentNode` in every loop.
                    returnValue.pop_back();
                    remainingTickets += 1;

                    auto previousNode = returnValue.back();
                    auto& previousDestinations = ticketsMap[previousNode];

                    auto currentNodeIt = std::find(previousDestinations.begin(), previousDestinations.end(), currentNode + ' ');
                    *currentNodeIt = currentNode;    // Mark as unvisited by removing the trailing space.

                    auto nextNodeIt = currentNodeIt + 1;
                    while ((nextNodeIt != previousDestinations.end()) && (nextNodeIt->size() == 4)) {    // Ignore visited nodes.
                        nextNodeIt += 1;
                    }
                    if (nextNodeIt != previousDestinations.end()) {
                        // We have a next node.
                        returnValue.push_back(*nextNodeIt);
                        remainingTickets -= 1;
                        nextNodeIt->push_back(' ');    // Mark as visited.

                        break;
                    }
                }
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<std::string>>& tickets, const std::vector<std::string> expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.findItinerary(tickets);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << tickets << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << tickets << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{"JFK","SFO"},{"SFO","JFK"},{"JFK","SFO"},{"SFO","JFK"},{"JFK","SFO"},{"SFO","JFK"}}, {"JFK","SFO","JFK","SFO","JFK","SFO","JFK"});
    test({{"EZE","TIA"},{"EZE","HBA"},{"AXA","TIA"},{"JFK","AXA"},{"ANU","JFK"},{"ADL","ANU"},{"TIA","AUA"},{"ANU","AUA"},{"ADL","EZE"},{"ADL","EZE"},{"EZE","ADL"},{"AXA","EZE"},{"AUA","AXA"},{"JFK","AXA"},{"AXA","AUA"},{"AUA","ADL"},{"ANU","EZE"},{"TIA","ADL"},{"EZE","ANU"},{"AUA","ANU"}}, {"JFK","AXA","AUA","ADL","ANU","AUA","ANU","EZE","ADL","EZE","ANU","JFK","AXA","EZE","TIA","AUA","AXA","TIA","ADL","EZE","HBA"});
    test({{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}}, {"JFK","NRT","JFK","KUL"});
    test({{"EZE","AXA"},{"TIA","ANU"},{"ANU","JFK"},{"JFK","ANU"},{"ANU","EZE"},{"TIA","ANU"},{"AXA","TIA"},{"TIA","JFK"},{"ANU","TIA"},{"JFK","TIA"}}, {"JFK","ANU","EZE","AXA","TIA","ANU","JFK","TIA","ANU","TIA","JFK"});
    test({{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}}, {"JFK","MUC","LHR","SFO","SJC"});
    test({{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}}, {"JFK","ATL","JFK","SFO","ATL","SFO"});

    return 0;
}
