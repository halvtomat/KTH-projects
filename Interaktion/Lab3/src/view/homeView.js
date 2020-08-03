class HomeView {
  constructor(container, gsc) {
    this.container = container;
    this.gsc = gsc;
  }
  
  // An example of creating HTML declaratively. Think about the pros and cons of this approach.
  render() {
  }

  afterRender() {
    this.container.querySelector("#startbtn").addEventListener("click",() => this.gsc.searchDishes());
  }
}
