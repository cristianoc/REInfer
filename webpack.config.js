const path = require("path");

module.exports = {
  entry: {
    index: "./src/Index.js"
  },
  mode: "production",
  output: {
    path: path.join(__dirname, "bundledOutputs"),
    filename: "webpack.js"
  }
};
