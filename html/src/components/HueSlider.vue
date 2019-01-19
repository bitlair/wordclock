<template>
  <div class="hueSlider">
    <input type="range" class="hue" min="0" max="255" id="formControlRange" v-bind:value="value"
      v-on:change="$emit('input', $event.target.value)"> {{ value }}
  </div>
</template>

<script>
export default {
  name: 'HueSlider',
  props: [ 'value' ]
}
</script>

<style>
input[type=range].hue {
  outline: 0;
  -webkit-appearance: none;
  width: 400px;
  height: 4px;
  background: linear-gradient(to right, hsl(0, 100%, 50%) 0%, hsl(30, 100%, 50%) 8.3%, hsl(60, 100%, 50%) 16.6%, hsl(90, 100%, 50%) 25%, hsl(120, 100%, 50%) 33.3%, hsl(150, 100%, 50%) 41.6%, hsl(180, 100%, 50%) 50%, hsl(210, 100%, 50%) 58.3%, hsl(240, 100%, 50%) 66.6%, hsl(270, 100%, 50%) 75%, hsl(300, 100%, 50%) 83.3%, hsl(330, 100%, 50%) 91.6%, hsl(360, 100%, 50%) 100%);
}
</style>