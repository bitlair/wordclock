<template>
  <div id="app">
    <b-container>
      <nav class="navbar navbar-expand-lg ">
        <a class="navbar-brand" href="#">
          <img alt="Bitlair logo" src="./assets/bitlair.svg" height="30">
        </a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>

        <div class="collapse navbar-collapse" id="navbarSupportedContent">
          <ul class="navbar-nav mr-auto">
            <li class="nav-item">
              <router-link to="/">Kleuren</router-link> 
            </li>
            <li class="nav-item">
              <router-link to="/wifi">WiFi</router-link> 
            </li>
            <li class="nav-item">
              <router-link to="/advanced">Geavanceerd</router-link> 
            </li>
            <li class="nav-item">
              <router-link to="/about">Informatie</router-link>
            </li>
          </ul>

          <span class="navbar-text">
            Wordclock
          </span>
        </div>
      </nav>

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
  padding: 30px;
  a {
    font-weight: bold;
    color: #2c3e50;
    &.router-link-exact-active {
      color: #42b983;
    }
  }
}
</style>
