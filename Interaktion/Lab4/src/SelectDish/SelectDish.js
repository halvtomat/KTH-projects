import React, { Component } from "react";
import Sidebar from "../Sidebar/Sidebar";
import Dishes from "../Dishes/Dishes";
import Details from "../Details/Details";
import Search from "../Search/Search";
import "./SelectDish.css";

class SelectDish extends Component {


  getDetails = (id) => {
    //path="/dish/"+id;
    console.log(id);
  }


  render() {
    return (
      <div className="SelectDish">
        <Search model={this.props.model}  />
        <Sidebar model={this.props.model} />
        <Dishes getDetails={this.getDetails}/>
      </div>
    );
  }
}

export default SelectDish;
