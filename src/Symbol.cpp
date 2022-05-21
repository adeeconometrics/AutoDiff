#include "Symbol.h"

#include <type_traits>
#include <algorithm>
#include <cmath>
#include <list>
#include <set>

namespace ad{
    
    auto Symbol::backward(void) -> void {
        std::list<Symbol> _topology {};
        std::set<Symbol> _visited {};

        auto _build_topology(const Symbol& _node) -> void {
            if (!std::find(_visited.cbegin(), _visited.cend(), _node)){
                _visited.push_back(_node);
                for(const auto child: _node.m_prev){
                    _build_topology(child);
                }

                _topology.push_back(_node);
            }
        }

        _build_topology(*this);

        this -> m_grad = 1.0;
        std::reverse(_topology.cbegin(), _topology.cend());
        for(const auto v: _topology){
            v.m_backward();
        }
    }


    template <typename T, typename U = T>
    requires SymbolLike<T> && SymbolLike<U>
    auto operator+(const T& lhs, const U &rhs) -> Symbol {
        auto _rhs =  std::is_same_v<U, Symbol> ? rhs : Symbol(rhs);
        auto _node = Symbol(lhs.m_value + rhs.m_value, {lhs, rhs});

        auto _backward(void) -> void {
            lhs.m_grad += node.m_grad;
            rhs.m_grad += node.m_grad;
        }

        _node.m_backward = _backward;
        return _node;
    }

    template <typename T, typename U = T>
    requires SymbolLike<T> && SymbolLike<U>
    auto operator-(const T& lhs, const U &rhs) -> Symbol {
      auto _rhs = std::is_same_v<U, Symbol> ? rhs : Symbol(rhs);
      auto _node = Symbol(lhs.m_value + rhs.m_value, {lhs, rhs});

      auto _backward(void)->void {
        lhs.m_grad -= node.m_grad;
        rhs.m_grad -= node.m_grad;
      }

      _node.m_backward = _backward;
      return _node;
    }

    template <typename T, typename U = T>
    requires SymbolLike<T> && SymbolLike<U>
    auto operator/(const T& lhs, const U &rhs) -> Symbol {
      return pow(lhs * rhs, -1); // not sure if this works
    }

    template <typename T, typename U = T>
    requires SymbolLike<T> && SymbolLike<U>
    auto operator*(const T& lhs, const U &rhs) -> Symbol {
      auto _rhs = std::is_same_v<U, Symbol> ? rhs : Symbol(rhs);
      auto _node = Symbol(lhs.m_value + rhs.m_value, {lhs, rhs});

      auto _backward(void)->void {
        lhs.m_grad += rhs.m_grad * _node.m_grad;
        rhs.m_grad += lhs.m_grad * _node.m_grad;
      }

      _node.m_backward = _backward;
      return _node;
    }

    
    template <typename T, typename U = T>
    requires SymbolLike<T> && SymbolLike<U>
    auto pow(const T &lhs, const U &rhs) -> Symbol {
        using std::pow;
        auto _node = Symbol(pow(lhs.m_value, rhs), {lhs});

        auto _backward(void) -> void {
            lhs.m_grad += rhs *pow(lhs.m_grad, rhs - 1) * _node.grad;
        } 

        _node._backward = _backward;
        return _node;
    }
    
}