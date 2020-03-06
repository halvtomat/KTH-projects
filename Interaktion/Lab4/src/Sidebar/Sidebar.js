import React, { Component } from "react";
import MenuItem from "../MenuItem/MenuItem"
import "./Sidebar.css";

class Sidebar extends Component {
  constructor(props) {
    super(props);

    // we put on state the properties we want to use and modify in the component
    this.state = {
      numberOfGuests: this.props.model.getNumberOfGuests(),
      menu: this.props.model.getFullMenu()
    };
  }

  // this methods is called by React lifecycle when the
  // component is actually shown to the user (mounted to DOM)
  // that's a good place to setup model observer
  componentDidMount() {
    this.props.model.addObserver(this);
  }

  // this is called when component is removed from the DOM
  // good place to remove observer
  componentWillUnmount() {
    this.props.model.removeObserver(this);
  }

  // in our update function we modify the state which will
  // cause the component to re-render
  update() {
    this.setState({
      numberOfGuests: this.props.model.getNumberOfGuests(),
      menu: this.props.model.getFullMenu()
    });
  }

  // our handler for the input's on change event
  onNumberOfGuestsChanged = e => {
    this.props.model.setNumberOfGuests(e.target.value);
  };

  render() {
    let menuitems = this.state.menu.map((dish) => (
      <MenuItem  dish={dish}/>
    ))
    console.log(this.state.menu);
    console.log(menuitems);
    return (
      <div className="Sidebar">
        <div className="Sidebar_top">
          <h3>This is the sidebar</h3>
          <p>
            People:
            <input
              type="number"
              value={this.state.numberOfGuests}
              onChange={this.onNumberOfGuestsChanged}
            />
          </p>
        </div>
        <div className="Sidebar_bottom">
          <ul>
            {menuitems}
          </ul>
        </div>
      </div>
    );
  }
}

export default Sidebar;
