<template>
  <div id="app">
    <b-container>
      <b-navbar toggleable="md">
        <b-navbar-toggle target="nav_collapse"></b-navbar-toggle>

        <b-navbar-brand href="#"><img alt="Bitlair logo" src="./assets/bitlair.svg" height="30"></b-navbar-brand>

        <b-collapse is-nav id="nav_collapse">

          <b-navbar-nav class="mr-auto">
            <li class="nav-item">
              <router-link to="/" class="nav-link">Kleuren</router-link> 
            </li>
            <li class="nav-item">
              <router-link to="/wifi" class="nav-link">WiFi</router-link> 
            </li>
            <li class="nav-item">
              <router-link to="/advanced" class="nav-link">Geavanceerd</router-link> 
            </li>
            <li class="nav-item">
              <router-link to="/about" class="nav-link">Informatie</router-link>
            </li>
          </b-navbar-nav>

          <b-nav-text>Woordklok</b-nav-text>
        </b-collapse>
      </b-navbar>

      <wifi-warning />

      <router-view/>
    </b-container>
  </div>
</template>

<style lang="less">
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}
.navbar {
  padding: 0px !important;
  margin-bottom: 20px;

  .nav-item {
    a {
      font-weight: bold;
      color: #000000;
      &.router-link-exact-active {
        color: #fc5d1dff;
      }
    }
  }
}
#wifialert {
  margin-top: 20px;
  margin-bottom: 20px;
}
</style>

<script>
import WifiWarning from '@/components/WifiWarning.vue'
import { mapState } from 'vuex'

export default {
  name: 'App',
  computed: mapState([ 'wifi' ]),
  components: {
    WifiWarning
  }
}
</script>