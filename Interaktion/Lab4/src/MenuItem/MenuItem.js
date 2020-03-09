import React, { Component } from "react";
import "./MenuItem.css";

class MenuItem extends Component {
  constructor(props) {
    super(props);
  }

  render() {
      console.log(this.props.dish);
    return ( 
        <div className="MenuItem">
            <div className="dishName">{this.props.dish.title}</div>
            <div className="dishPrice">SEK: {this.props.dish.pricePerServing * this.props.model.getNumberOfGuests()}</div>
            <button className="removeItem" onClick={() => this.props.model.removeDishFromMenu(this.props.dish.id)}>X</button>
        </div>     
    );
  }
}

export default MenuItem;
