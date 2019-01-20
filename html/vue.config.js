module.exports = {
  devServer: {
  	proxy: {
      '/api': {
        target: 'http://100.64.0.30',
        ws: true,
        changeOrigin: true
      }
    }
  }  
}