import resolve from "rollup-plugin-node-resolve";
import commonjs from "rollup-plugin-commonjs";

export default {
  input: "src/Index.js",
  output: {
    file: "bundledOutputs/rollup.js",
    format: "umd",
    name: "main"
  },
  plugins: [
    // resolve(),
    commonjs({
      include: "node_modules/**",
      namedExports: {
        // left-hand side can be an absolute path, a path
        // relative to the current directory, or the name
        // of a module in node_modules
        "react-dom": ["render", "hydrate"],
        react: ["createElement", "useReducer"]
      }
    })
  ],
  //  external: ["react", "react-dom"],
  globals: {
    //    react: "React"
  }
};
