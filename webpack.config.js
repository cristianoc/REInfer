const path = require("path");

const isProd = process.env.NODE_ENV === "production";

module.exports = {
  entry: {
    index: "./src/Index.js"
  },
  mode: "production",
  output: {
    path: path.join(__dirname, "bundledOutputs"),
    filename: "[name].js"
  },
  optimization: {
    usedExports: true
  }
};
