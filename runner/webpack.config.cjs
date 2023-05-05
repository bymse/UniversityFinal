const path = require('path');

module.exports = {
  entry: './static/browser.js',
  output: {
    path: path.resolve(__dirname, 'static', 'build'),
    filename: 'browser.js',
  },
};