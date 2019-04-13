/*!
 *  Copyright (c) 2019 by Contributors.
 * \file tvm/relay/pass/dependency_graph.h
 * \brief 
 */
#ifndef TVM_RELAY_PASS_DEPENDENCY_GRAPH_H_
#define TVM_RELAY_PASS_DEPENDENCY_GRAPH_H_

#include <tvm/relay/expr.h>
#include <unordered_map>
#include <vector>
#include "let_list.h"
#include "../../common/arena.h"

namespace tvm {
namespace relay {

using common::LinkNode;
using common::LinkedList;

/* DependencyGraph track input and output of an Expr.
 * Additionally, dummy scope is created to model scope.
 * It allow us to traverse the graph in reverse order.
 */
class DependencyGraph {
 public:
  /*! \brief A node in the graph. */
  struct Node {
    // Determine scope boundaries. Used for calculating scopes, not for
    // constructing dependency graph.
    bool new_scope = false;
    // incoming edges
    LinkedList<Node*> children;
    // outgoing edges
    LinkedList<Node*> parents;
  };

  /*! \brief Maps a Relay Expr to its node in the dependency graph. */
  std::unordered_map<Expr, Node*, NodeHash, NodeEqual> expr_node;

  /*! \brief The dependency graph in post DFS order. */
  std::vector<Node*> post_dfs_order;

  /*!
   * \brief Create a dependency graph.
   * \param arena The arena used for data allocation.
   * \param body The body of the expression to create a graph.
   */
  static DependencyGraph Create(common::Arena* arena, const Expr& body);

 private:
  class Creator;
};

}  // namespace relay
}  // namespace tvm
#endif  // TVM_RELAY_PASS_DEPENDENCY_GRAPH_H_
