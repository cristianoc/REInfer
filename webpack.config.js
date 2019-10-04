const path = require("path");

const isProd = process.env.NODE_ENV === "production";

module.exports = {
  entry: {
    index: "./src/Index.bs.js"
  },
  mode: isProd ? "production" : "development",
  output: {
    path: path.join(__dirname, "bundledOutputs"),
    filename: "[name].js"
  }
};
