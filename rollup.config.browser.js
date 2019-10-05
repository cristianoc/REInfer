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
    resolve(),
//    commonjs()
  ],
  //  external: ["react", "react-dom"],
  globals: {
    //    react: "React"
  }
};
