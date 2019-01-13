import Vue from 'vue'
import Router from 'vue-router'
import Colors from './views/Colors.vue'
import About from './views/About.vue'
import Wifi from './views/Wifi.vue'
import Advanced from './views/Advanced.vue'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'colors',
      component: Colors
    },
    {
      path: '/about',
      name: 'about',
      component: About
    },
    {
      path: '/wifi',
      name: 'wifi',
      component: Wifi
    },
    {
      path: '/advanced',
      name: 'advanced',
      component: Advanced
    }
  ]
})
