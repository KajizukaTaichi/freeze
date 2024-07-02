import lark
from llvmlite import ir
import collections

def parser(sourcefile: str) -> lark.tree.Tree:
    sourcecode = str()
    grammar = str()
    with open(sourcefile, "r") as file:
        sourcecode = file.read()
    with open("./data/syntax.lark", "r") as file:
        grammar = file.read()
    return lark.Lark(grammar, start="lang", parser="lalr").parse(sourcecode)

class genir(lark.visitors.Interpreter):
    def __init__(self) -> None:
        super().__init__()
        self.module = ir.Module()
        self.env = collections.deque()
        self.builders = dict()
    def lang(self, tree):
        self.env.append({"main": ir.Function(self.module, ir.FunctionType(ir.IntType(32), list()), "main")})
        self.builders["main"] = ir.IRBuilder(self.env.popleft()["main"].append_basic_block())
        return self.visit(tree.children[0])
    def program(self, tree):
        ret = None
        for statement in tree.children:
            ret = self.visit(statement)
        return ret
    def statement_group(self, tree):
        return self.visit(tree.children[0])

    

    # md_expr
    def mul(self, tree):
        return self.builders["current"].mul(self.visit(tree.children[0]), self.visit(tree.children[2]))
    def div(self, tree):
        return self.builders["current"].sdiv(self.visit(tree.children[0]), self.visit(tree.children[2]))
    def sur(self, tree):
        return self.builders["curremt"].srem(self.visit(tree.children[0]), self.visit(tree.children[2]))

    # base_expr
    def number(self, tree):
        return ir.Constant(ir.FloatType(), float(tree.children[0].value))
    def string(self, tree):
        temp = str(tree.children[1].value)
        return ir.Constant(ir.ArrayType(ir.IntType(8), len(temp) + 1), bytearray(temp.encode("utf-8") + b"\00"))
    def name(self, tree):
        return str(tree.children[0].value)
    def function_call(self, tree):
        name = self.visit(tree.children[0])
        args = self.visit(tree.children[2])
        return self.builders["current"].call(self.env[name], args)
    def variable_call(self, tree):
        return self.builders["current"].load(self.env[self.visit(tree.children[1])])
    def arg_call(self, tree):
        return [self.visit(arg) for arg in tree.children]
    def argc_e(self, tree):
        return self.visit(tree.children[0])
    def data_expr(self, tree):
        return self.visit(tree.children[0])
    def eexpr_(self, tree):
        return self.visit(tree.children[1])
