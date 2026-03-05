# Visual Data Studio - Visual Dashboard Designer

[![License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](LICENSE)
[![Qt](https://img.shields.io/badge/Qt-6.8.1-41CD52.svg)](https://www.qt.io/)
[![Language](https://img.shields.io/badge/C++-20-00599C.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)]()

For Chinese documentation, please visit [README.md](README.md).

---

## Introduction

Visual Data Studio is a **Visual Dashboard Designer** built with Qt 6.8.1, featuring a modular plugin architecture. It supports drag-and-drop graphic editing, data binding, animation configuration, and real-time preview. This software is designed specifically for data visualization scenarios, helping users quickly create professional data presentation interfaces.

**Both graphic components and data sources are designed with a plugin architecture. Users can develop custom extensions according to their needs.**

## Core Features

### 🎨 Visual Editing
- **Drag-and-Drop Design**: Drag graphic elements from the component library to the canvas, supporting rectangles, circles, lines, text, charts, and various other graphics
- **Property Editing**: Visual property panel for real-time modification of graphic styles, position, size, color, borders, etc.
- **Layer Management**: Tree-based layer display with layer ordering, show/hide, lock operations
- **Auxiliary Tools**: Grid, ruler, reference lines, alignment guides for precise layout control

### 📊 Graphic Components (Plugin-based Design)
- **Basic Shapes**: Rectangles, circles, ellipses, lines, polygons, paths, etc.
- **Text Components**: Rich text support, custom fonts, colors, alignment options
- **Chart Support**: Integrated Google Charts, supporting line charts, bar charts, pie charts, scatter plots, and more
- **Custom Components**: Support for importing SVG graphics, images, and user-defined component libraries
- **Plugin Extensions**: All graphic components are loaded via plugin mechanism, supporting custom graphic plugin development

### 💾 Data Binding (Plugin-based Design)
- **Multiple Data Sources**:
  - Databases (MySQL, PostgreSQL, SQLite, etc.)
  - HTTP APIs (RESTful API support with OAuth1, OAuth2, JWT, Basic Auth, and various authentication methods)
  - Data Directory (local data source management)
- **Data Mapping**: Process data through JavaScript scripts to implement data-to-property mapping
- **Data Operations**: Support for data assignment, control, editing, and various other operations
- **Real-time Updates**: Timed data refresh support for real-time monitoring
- **Plugin Extensions**: All data sources are loaded via plugin mechanism, supporting custom data source plugin development

### ✨ Animation Effects
- **Move Animation**: Linear, curved, and polygon path animations
- **Transform Animation**: Rotation, scaling, opacity changes
- **Blink Effect**: Blink animation support
- **Path Editing**: Visual path editor with Bezier curve control

### 🔧 Editing Functions
- **Undo/Redo**: Complete command pattern implementation with multi-level undo/redo support
- **Alignment & Distribution**: Left, right, top, bottom alignment, center alignment, horizontal/vertical distribution
- **Layer Adjustment**: Bring to front, send to back, bring forward, send backward
- **Group/Ungroup**: Support for combining multiple graphics into a group, or ungrouping
- **Flip**: Horizontal flip, vertical flip

### 📁 Project Management
- **Project Save**: Save as `.bi` format project files containing all graphics, animations, and data configurations
- **Project Export**: Export to PNG, JPG, SVG, and other image formats
- **Component Library**: Custom component library support for saving common designs as reusable components

## System Architecture

Visual Data Studio adopts a **modular plugin architecture**, where both graphic components and data sources are loaded via plugin mechanisms. Users can develop custom extensions according to their needs.

### Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                     Visual Data Studio                          │
│                      (Main Application)                         │
└─────────────────────────────────────────────────────────────────┘
                                  │
                    ┌─────────────┴─────────────┐
                    ▼                           ▼
         ┌────────────────────┐      ┌────────────────────┐
         │   Graphic Engine   │      │    Data Engine     │
         └────────────────────┘      └────────────────────┘
                    │                           │
                    │ Plugin Interface          │ Plugin Interface
                    ▼                           ▼
         ┌────────────────────┐      ┌────────────────────────┐
         │  Graphic Plugins   │      │ Data Source Plugins    │
         └────────────────────┘      └────────────────────────┘
         │        │        │            │          │          │
         ▼        ▼        ▼            ▼          ▼          ▼
    ┌──────┐ ┌──────┐ ┌────────┐    ┌──────┐   ┌────────┐ ┌──────┐
    │Basic │ │Chart │ │Custom  │    │Custom│   │Database│ │HTTP  │
    │Shapes│ │Comps │ │Graphics│    │Data  │   │Plugin  │ │Plugin│
    └──────┘ └──────┘ └────────┘    │Source│   └────────┘ └──────┘
                                    │Plugin│
                                    └──────┘
                                 
Core Modules:
├── GraphicsManager
│   ├── Plugin loading and management
│   ├── Graphic creation and destruction
│   └── Graphic serialization
├── DataSourcePluginManager
│   ├── Plugin loading and management
│   ├── Data request and response
│   └── Data processing and mapping
├── AnimationFactory
│   ├── Animation definition and execution
│   └── Path editing and management
└── ProjectManager
    ├── Project save and load
    └── Export functionality
```

## Use Cases

Visual Data Studio is suitable for various data visualization and dashboard design scenarios:

### 🏢 Enterprise Large Screens
- Create real-time data monitoring large screens
- Display enterprise KPIs, sales data, production data, etc.
- Support multi-source data aggregation display

### 📈 Data Reports
- Create interactive data reports
- Support charts, tables, metric cards, and various display methods
- Support data refresh and real-time updates

### 🏭 Industrial Monitoring
- Industrial equipment status monitoring
- Production line data visualization
- Alarm and anomaly status display

### 📊 Business Analytics
- Sales performance analysis dashboard
- User behavior analysis
- Operations data display

### 🎓 Educational Demonstrations
- Data visualization teaching
- Chart creation demonstrations
- Interactive teaching tools

### 🌐 Internet of Things (IoT)
- Smart device data display
- Sensor data visualization
- Device status monitoring dashboard

## Screenshots

![Main Interface](screenshots/1.png)

![Graphic Editing](screenshots/2.png)

![Property Panel](screenshots/3.png)

![Chart Components](screenshots/4.png)

![Data Binding](screenshots/5.png)

![Animation Configuration](screenshots/6.png)

![Export Options](screenshots/7.png)

## License

This project is licensed under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

---

For Chinese documentation, please visit [README.md](README.md).
