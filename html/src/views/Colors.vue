<template>
  <div class="colors">
    <h1>Kleur instellingen</h1>

    <div>
      <input type="radio" id="single" value="single" v-model="mode">
      <label for="single">Enkele kleur</label>
      <input type="radio" id="rainbow" value="rainbow" v-model="mode">
      <label for="rainbow">Regenboog</label>
      <input type="radio" id="words" value="words" v-model="mode">
      <label for="words">Per woord</label>
      <input type="radio" id="hourly" value="hourly" v-model="mode">
      <label for="hourly">Per uur</label>
    </div>

    <div class="settings">
      <colors-single v-if="mode === 'single'" />

      <template v-if="mode === 'rainbow'">
        In regenboog mode zal de woordklok automatisch geleidelijk van kleur veranderen. 
        Er zijn in deze stand geen kleur instellingen mogelijk.
      </template>

      <colors-words v-if="mode === 'words'" />
      <colors-hourly v-if="mode === 'hourly'" />
    </div>
  </div>

</template>

<script>
import ColorsSingle from '@/views/Colors-Single.vue'
import ColorsWords from '@/views/Colors-Words.vue'
import ColorsHourly from '@/views/Colors-Hourly.vue'

export default {
  name: 'home',
  computed: {
    mode: {
      get () {
        return this.$store.state.leds.mode
      },
      set (value) {
        this.$store.commit('ledMode', value)
        this.axios.get('/api/led/mode', { params: { mode: value }} )
      }
    }
  },
  components: {
    ColorsSingle,
    ColorsWords,
    ColorsHourly
  }
}
</script>
