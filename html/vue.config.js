module.exports = {
  devServer: {
  	proxy: {
      '/api': {
        target: 'http://10.0.1.161',
        ws: true,
        changeOrigin: true
      }
    }
  }  
}