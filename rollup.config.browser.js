import resolve from "rollup-plugin-node-resolve";
import commonjs from "rollup-plugin-commonjs";
import replace from "rollup-plugin-replace";
import { uglify } from "rollup-plugin-uglify";

export default {
  input: "src/Index.js",
  output: {
    file: "bundledOutputs/rollup.js",
    format: "iife",
    name: "main"
  },
  plugins: [
    resolve(),
    commonjs({
      include: "node_modules/**",
      namedExports: {
        // left-hand side can be an absolute path, a path
        // relative to the current directory, or the name
        // of a module in node_modules
        "react-dom": ["render", "hydrate"],
        react: ["createElement", "useReducer"]
      }
    }),
    replace({
      "process.env.NODE_ENV": "'production'"
    }),
    uglify()
  ]
};
