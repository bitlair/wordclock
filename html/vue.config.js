module.exports = {
  devServer: {
  	proxy: {
      '/api': {
        target: 'http://10.0.1.150',
        ws: true,
        changeOrigin: true
      }
    }
  }  
}