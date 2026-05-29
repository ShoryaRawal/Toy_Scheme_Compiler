#include "runtime/evaluator.hpp"

#include <stdexcept>
#include <variant>

namespace tscm{
	Value Evaluator::evaluate_program(const CoreProgram & program){
		Value result;

		for(const auto & expr : program.expressions) 
			result = evaluate_expression(expr);
		
		return result;
	}

	Value Evaluator::evaluate_expression(const CoreExprPtr & expr){
		return std::visit(
			[&] (const auto & node) -> Value {
				using T = std::decay_t<decltype(node)>;
				if constexpr (std::is_same_v<T, CoreIntegerExpr>){
					return Value(node.value);
				} else if constexpr(std::is_same_v<T, CoreVariableExpr>){
					return global_environment_.lookup(node.name);
				}else if constexpr (std::is_same_v<T, CoreDefineExpr>){
					Value value = evaluate_expression(node.value);
					global_environment_.define(node.name, value);

					return value;
				} else if constexpr (std::is_same_v<T, CoreCallExpr>){
					return evaluate_call(node);
				} else throw std::runtime_error("Unsupported runtime expression");
			},
			expr -> value
		);
	}

	Value Evaluator::evaluate_call(const CoreCallExpr & call){
		const auto * callee = std::get_if<CoreVariableExpr>( &call.callee -> value );
		if(!callee) throw std::runtime_error("callable expression required");

		std::vector<Value> args;

		for(const auto & arg : call.arguments) args.push_back(evaluate_expression(arg));

		const std::string & name = callee -> name;
		
		if(name == "+") {
			std::int64_t result = 0;
			for (const auto & value : args)  result += value.as_integer();

			return Value(result);
		} else if(name == "-") {
			if(args.empty()) throw std::runtime_error(" - requires arguments");

			std::int64_t result = args[0].as_integer();
			for(std::size_t i = 1; i < args.size(); ++i) 
				result -= args[i].as_integer();

			return Value(result);
		} else if(name == "*"){
			std::int64_t result = 1;
			for (const auto & value : args) result *= value.as_integer();

			return Value(result);
		} else if(name == "/"){
			if(args.empty()) throw std::runtime_error(" - requires arguments");

			std::int64_t result = args[0].as_integer();
			for(std::size_t i = 1; i < args.size(); ++i) 
				result /= args[i].as_integer();

			return Value(result);
		} else if(name == "%"){
			if(args.size() != 2) 
				throw std::runtime_error("- requires exactly 2 arguments");

			return Value( args[0].as_integer() % args[1].as_integer() );
		} else throw std::runtime_error("Unkown function: " + name);
	}
}
