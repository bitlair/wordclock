module.exports = {
  devServer: {
  	proxy: {
      '/api': {
        target: 'http://100.64.0.69',
        ws: true,
        changeOrigin: true
      }
    }
  }  
}